/**
 * @file event_manager.hpp
 * @author Daniel Parker
 * @brief Manages event distribution and subscriptions.
 * @version 0.1
 * @date 2026-02-27
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <algorithm>
#include <functional>
#include <queue>
#include <typeinfo>
#include <unordered_map>
#include <vector>

namespace HBE::Application::Managers {
    /**
     * @struct SubscriptionHandle
     * @brief Unique identifier for a subscription, used to unsubscribe later.
     *
     * Returned by Subscribe() and can be passed to Unsubscribe() to remove a listener.
     */
    struct SubscriptionHandle {
        uint64_t id = 0;

        /// @brief Check if two handles refer to the same subscription
        bool operator==(const SubscriptionHandle &other) const { return id == other.id; }
        bool operator!=(const SubscriptionHandle &other) const { return id != other.id; }
    };

    /**
     * @class EventManager
     * @brief Centralized event distribution system for the application.
     *
     * Handles event subscription, emission, and dispatch. Events are queued and dispatched
     * once per frame to maintain consistent event ordering and timing.
     *
     * ## Architecture
     *
     * The EventManager uses **type erasure** to support multiple event types in a single container.
     * This allows heterogeneous event storage without templates at the container level.
     *
     * ### Type Erasure Pattern:
     * ```
     * EventSubsBase (abstract)
     *     ↓
     * EventSubs<OnEnterEvent> (concrete)
     *     ↓
     * stores vector<function<void(const OnEnterEvent&)>>
     * ```
     *
     * This design enables:
     * - Storing subscribers for different event types in one map
     * - Type-safe event dispatch through template specialization
     * - Extensibility without modifying the core system
     *
     * ### Event Flow:
     * 1. **Subscribe phase** (during setup): Register listeners for specific event types
     * 2. **Emit phase** (during game logic): Queue events for dispatch
     * 3. **Dispatch phase** (after rendering): invoke all listeners and clear queue
     *
     * ## Usage Example
     *
     * @code
     *   // 1. Subscribe to an event (typically in OnStart or setup)
     *   g_app.GetEventManager().Subscribe<OnEnterEvent>(
     *       [](const OnEnterEvent& evt) {
     *           LOG(LoggingType::INFO, "Button hovered: " + std::to_string(evt.entity_id));
     *       }
     *   );
     *
     *   // 2. Emit an event during frame update
     *   g_app.GetEventManager().Emit(OnEnterEvent{entity_id});
     *
     *   // 3. Dispatch queued events (called automatically in Application::OnPostRender)
     *   g_app.GetEventManager().DispatchAll();
     * @endcode
     *
     * ## Thread Safety
     * Not thread-safe. All subscription and emission must occur on the main game thread.
     * All dispatch occurs at frame end (OnPostRender), ensuring single-threaded event handling.
     *
     * @see OnEnterEvent
     * @see OnExitEvent
     * @see OnClickEvent
     */
    class EventManager {
    private:
        /**
         * @struct EventSubsBase
         * @brief Abstract base for type-erased event subscriber containers.
         *
         * Uses virtual dispatch to invoke listeners regardless of the actual EventType.
         * This allows storing EventSubs<OnEnterEvent>, EventSubs<OnClickEvent>, etc.,
         * in a single unordered_map without knowing their concrete types.
         *
         * @note Only used internally for type erasure; not meant for direct use.
         */
        struct EventSubsBase {
            virtual ~EventSubsBase() = default;

            /**
             * @brief Dispatch an event to all subscribers of this type.
             * @param event Pointer to the queued event data (will be cast to actual EventType in subclass)
             *
             * Implementation is in EventSubs<EventType> specialization.
             */
            virtual void Dispatch(void *event) = 0;

            /**
             * @brief Remove a subscription by ID without knowing the event type.
             * @param id The subscription ID to remove
             * @return True if removed, false if not found
             *
             * Allows type-erased removal of subscriptions.
             */
            virtual bool RemoveSubscriptionById(uint64_t id) = 0;
        };

        /**
         * @struct EventSubs<EventType>
         * @brief Template specialization storing listeners for a specific event type.
         *
         * Each specialization (e.g., EventSubs<OnEnterEvent>) holds a vector of
         * callbacks that expect that specific event type. When dispatched, it invokes
         * each callback with the properly-typed event object.
         *
         * @tparam EventType The concrete event struct (e.g., OnEnterEvent)
         *
         * @example
         * EventSubs<OnEnterEvent> stores:
         *   map<uint64_t, function<void(const OnEnterEvent&)>>
         *
         * So subscribers can be:
         *   - Lambda captures
         *   - std::bind to member functions
         *   - Function pointers
         *   - Any callable matching the signature
         */
        template <typename EventType>
        struct EventSubs : public EventSubsBase {
            /// Stores subscribers with unique IDs for unsubscribe support
            struct Subscription {
                uint64_t id;
                std::function<void(const EventType &)> listener;
            };

            std::vector<Subscription> subscriptions;

            /**
             * @brief Dispatch this event to all registered listeners.
             * @param event Void pointer to the event data (casted to EventType* internally)
             *
             * Iterates through all listeners and invokes each with the properly-typed event.
             */
            void Dispatch(void *event) override {
                // The void* is actually pointing to an EventType object
                EventType *typed_event = static_cast<EventType *>(event);
                for (const auto &sub : subscriptions) {
                    sub.listener(*typed_event);
                }
            }

            /// Remove subscription by ID
            bool RemoveSubscription(uint64_t id) {
                auto it = std::find_if(subscriptions.begin(), subscriptions.end(),
                                       [id](const Subscription &s) { return s.id == id; });
                if (it != subscriptions.end()) {
                    subscriptions.erase(it);
                    return true;
                }
                return false;
            }

            /// Virtual override for type-erased removal
            bool RemoveSubscriptionById(uint64_t id) override { return RemoveSubscription(id); }
        };

        /**
         * @struct QueuedEvent
         * @brief Opaque wrapper for a queued event, waiting for dispatch.
         *
         * Stores just enough information to dispatch an event later without knowing
         * its concrete type at storage time.
         */
        struct QueuedEvent {
            /// Type information (used as key to find the correct EventSubs container)
            std::type_info const *type;

            /// Lambda that will dispatch the event to the appropriate EventSubs container
            std::function<void(EventSubsBase &)> dispatch;
        };

        /// Maps from event type name (typeid) to its subscriber container
        std::unordered_map<std::string, std::unique_ptr<EventSubsBase>> m_subscribers;

        /// Maps subscription ID to its event type key for type-erased unsubscribe
        std::unordered_map<uint64_t, std::string> m_subscription_types;

        /// Queue of events emitted this frame, waiting to be dispatched at frame end
        std::queue<QueuedEvent> m_event_queue;

        /// Counter for generating unique subscription handles
        uint64_t m_next_subscription_id = 1;

        /**
         * @brief Get a unique key for an event type.
         * @tparam EventType The event type
         * @return String representation of the type (from std::typeid)
         *
         * Used internally to map event types to their subscriber containers.
         */
        template <typename EventType>
        std::string GetEventKey() const {
            return typeid(EventType).name();
        }

    public:
        EventManager() = default;
        ~EventManager() = default;

        /**
         * @brief Subscribe to an event type.
         *
         * Registers a listener callback to be invoked whenever an event of the
         * specified type is dispatched. Multiple listeners can subscribe to the
         * same event type.
         *
         * @tparam EventType The event type to subscribe to (must be a struct with event data)
         * @param listener Callable that accepts `const EventType&` and returns void
         * @return SubscriptionHandle that can be used to unsubscribe later
         *
         * @example
         * @code
         *   auto handle = g_app.GetEventManager().Subscribe<OnEnterEvent>(
         *       [](const OnEnterEvent& evt) {
         *           std::cout << "Button " << evt.entity_id << " hovered! \n";
         *       }
         *   );
         *
         *   // Later, to unsubscribe:
         *   g_app.GetEventManager().Unsubscribe(handle);
         * @endcode
         *
         * @note Each subscription gets a unique handle. Storing the handle allows
         *       you to remove the listener at any time with Unsubscribe().
         */
        template <typename EventType>
        SubscriptionHandle Subscribe(std::function<void(const EventType &)> listener) {
            std::string key = GetEventKey<EventType>();

            // Lazy-create the EventSubs container for this type if it doesn't exist
            if (m_subscribers.find(key) == m_subscribers.end()) {
                m_subscribers[key] = std::make_unique<EventSubs<EventType>>();
            }

            // Allocate a unique ID for this subscription
            uint64_t subscription_id = m_next_subscription_id++;

            // Add this listener to the container for this event type
            auto *subs = static_cast<EventSubs<EventType> *>(m_subscribers[key].get());
            subs->subscriptions.push_back({subscription_id, listener});

            // Track the event type for this subscription ID
            m_subscription_types[subscription_id] = key;

            return SubscriptionHandle{subscription_id};
        }

        /**
         * @brief Emit an event to be dispatched later.
         *
         * Queues an event for dispatch at frame end (in DispatchAll). The event is
         * not immediately delivered to listeners; instead, it's buffered and delivered
         * in order during the DispatchAll phase.
         *
         * @tparam EventType The event type being emitted
         * @param event The event instance containing data for subscribers
         *
         * @example
         * @code
         *   // In UISystem::OnUpdateButton()
         *   if (button_just_entered_hover) {
         *       g_app.GetEventManager().Emit(OnEnterEvent{entity_id});
         *   }
         * @endcode
         *
         * @note Events are queued, not dispatched immediately. This ensures all
         *       systems complete their updates before event handlers run, preventing
         *       mid-frame reentrancy issues.
         *
         * @see DispatchAll()
         */
        template <typename EventType>
        void Emit(const EventType &event) {
            std::string key = GetEventKey<EventType>();

            QueuedEvent queued;
            queued.type = &typeid(EventType);
            // Capture the event and create a dispatch lambda that will invoke all listeners
            queued.dispatch = [event](EventSubsBase &subs) {
                auto *typed_subs = static_cast<EventSubs<EventType> *>(&subs);
                for (const auto &sub : typed_subs->subscriptions) {
                    sub.listener(event);
                }
            };

            m_event_queue.push(queued);
        }

        /**
         * @brief Dispatch all queued events to their registered listeners.
         *
         * Processes the event queue in FIFO order, invoking all listeners for each
         * event type. Should be called exactly once per frame, typically at the end
         * of the game loop (in Application::OnPostRender).
         *
         * After dispatch, the queue is cleared and ready for the next frame.
         *
         * @example Frame Flow:
         * ```
         * Frame start:
         *   OnUpdate() -> Systems emit events (queued)
         *   OnRender() -> Rendering happens
         *   OnPostRender() -> DispatchAll() <- Event dispatch happens here
         * Frame end
         * ```
         *
         * @note This is called automatically by Application, not manually by users.
         *
         * @see Application::OnPostRender()
         */
        void DispatchAll() {
            while (!m_event_queue.empty()) {
                QueuedEvent &queued = m_event_queue.front();

                // Look up the subscriber container for this event type
                std::string key = queued.type->name();
                auto it = m_subscribers.find(key);

                // If there are subscribers for this event type, dispatch to them
                if (it != m_subscribers.end()) {
                    queued.dispatch(*it->second);
                }

                m_event_queue.pop();
            }
        }

        /**
         * @brief Clear all queued events without dispatching them.
         *
         * Useful for flushing pending events when unloading scenes or resetting state.
         *
         * @example
         * @code
         *   // When stopping the game, discard any pending events
         *   m_event_manager->ClearQueue();
         * @endcode
         */
        void ClearQueue() { m_event_queue = std::queue<QueuedEvent>(); }

        /**
         * @brief Unsubscribe a listener from an event (without specifying the event type).
         *
         * Removes a previously registered listener using the handle returned by Subscribe().
         * After unsubscribing, the listener will no longer be invoked for events of that type.
         * The event type is automatically determined from the subscription record.
         *
         * @param handle The SubscriptionHandle returned by Subscribe()
         * @return True if the subscription was found and removed, false if handle was invalid
         *
         * @example
         * @code
         *   auto handle = g_app.GetEventManager().Subscribe<OnEnterEvent>(
         *       [](const OnEnterEvent& evt) { }
         *   );
         *
         *   // Later, stop listening to this event (type determined automatically)
         *   g_app.GetEventManager().Unsubscribe(handle);
         * @endcode
         *
         * @note If the handle is invalid or already unsubscribed, this will
         *       silently return false. It is safe to call Unsubscribe multiple times with
         *       the same (or invalid) handle.
         */
        bool Unsubscribe(SubscriptionHandle handle) {
            if (handle.id == 0) {
                return false; // Invalid handle
            }

            auto type_it = m_subscription_types.find(handle.id);
            if (type_it == m_subscription_types.end()) {
                return false; // Subscription not found
            }

            std::string key = type_it->second;
            auto sub_it = m_subscribers.find(key);

            if (sub_it != m_subscribers.end()) {
                bool removed = sub_it->second->RemoveSubscriptionById(handle.id);
                if (removed) {
                    m_subscription_types.erase(type_it);
                }
                return removed;
            }

            return false; // Event type container not found
        }

        /**
         * @brief Check if a subscription handle is valid and still active.
         *
         * @tparam EventType The event type to check
         * @param handle The SubscriptionHandle to validate
         * @return True if the subscription exists and is active
         *
         * @example
         * @code
         *   if (g_app.GetEventManager().IsSubscriptionActive<OnEnterEvent>(handle)) {
         *       // Subscription is still active
         *   }
         * @endcode
         */
        template <typename EventType>
        bool IsSubscriptionActive(SubscriptionHandle handle) const {
            if (handle.id == 0) {
                return false;
            }

            std::string key = GetEventKey<EventType>();
            auto it = m_subscribers.find(key);

            if (it != m_subscribers.end()) {
                const auto *subs = static_cast<const EventSubs<EventType> *>(it->second.get());
                return std::any_of(
                    subs->subscriptions.begin(), subs->subscriptions.end(),
                    [handle](const typename EventSubs<EventType>::Subscription &s) { return s.id == handle.id; });
            }

            return false;
        }

        /**
         * @brief Get the number of events currently in the dispatch queue.
         * @return Number of events pending dispatch
         *
         * Useful for debugging or monitoring event system performance.
         */
        size_t GetQueuedEventCount() const { return m_event_queue.size(); }
    };
} // namespace HBE::Application::Managers

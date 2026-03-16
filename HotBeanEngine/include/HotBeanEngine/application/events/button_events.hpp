/**
 * @file button_events.hpp
 * @author Daniel Parker
 * @brief Event structures for button interactions.
 * @version 0.1
 * @date 2026-02-27
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <HotBeanEngine/core/entity.hpp>

namespace HBE::Application::Events {
    using Core::EntityID;

    /**
     * @struct ButtonHoverEnterEvent
     * @brief Emitted when mouse enters a button's bounds.
     */
    struct ButtonEnterEvent {
        EntityID entity_id;
    };

    /**
     * @struct ButtonHoverExitEvent
     * @brief Emitted when mouse exits a button's bounds.
     */
    struct ButtonExitEvent {
        EntityID entity_id;
    };

    /**
     * @struct ButtonClickEvent
     * @brief Emitted when a button is clicked.
     */
    struct ButtonClickEvent {
        EntityID entity_id;
    };
} // namespace HBE::Application::Events

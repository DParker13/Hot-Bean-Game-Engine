/**
 * @file interact_system.hpp
 * @author Daniel Parker (DParker13)
 * @brief System for 2D UI management.
 * @version 0.1
 * @date 2026-03-17
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <HotBeanEngine/application/events/interactive_events.hpp>
#include <HotBeanEngine/core/system.hpp>
#include <HotBeanEngine/defaults/components/miscellaneous/transform_2d.hpp>
#include <HotBeanEngine/defaults/components/rendering/texture.hpp>
#include <HotBeanEngine/defaults/components/ui/interactive.hpp>

namespace HBE::Default::Systems {
    using Components::Interactive;
    using Components::Texture;
    using Components::Transform2D;
    using Core::EntityID;

    /**
     * @brief Manages UI elements (Interactive, Checkboxes, etc).
     * Renders element to their texture and handles user interaction.
     */
    class InteractSystem : public Core::GameSystem<Transform2D, Texture, Interactive> {
    public:
        DEFINE_NAME("Interact System")

    private:
        SDL_FPoint m_previous_mouse_position = {0.0f, 0.0f};
        SDL_FPoint m_current_mouse_position = {0.0f, 0.0f};
        bool m_has_mouse_position_sample = false;

        bool DidMouseSweepThroughRect(const SDL_FRect &rect) const;

    public:
        InteractSystem() = default;
        ~InteractSystem() = default;

        // System interface
        void OnEvent(SDL_Event &event) override;
        void OnUpdate() override;
    };
} // namespace HBE::Default::Systems
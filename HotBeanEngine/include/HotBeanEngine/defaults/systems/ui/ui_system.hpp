/**
 * @file ui_system.hpp
 * @author Daniel Parker (DParker13)
 * @brief System for 2D UI management.
 * @version 0.1
 * @date 2025-03-02
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <unordered_set>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <HotBeanEngine/application/events/button_events.hpp>
#include <HotBeanEngine/core/system.hpp>
#include <HotBeanEngine/defaults/components/miscellaneous/transform_2d.hpp>
#include <HotBeanEngine/defaults/components/rendering/texture.hpp>
#include <HotBeanEngine/defaults/components/ui/ui_element.hpp>

namespace HBE::Default::Systems {
    using Components::Texture;
    using Components::Transform2D;
    using Components::UIElement;
    using Core::EntityID;

    /**
     * @brief Manages UI elements (Buttons, Checkboxes, etc).
     * Renders element to their texture and handles user interaction.
     */
    class UISystem : public Core::GameSystem<Transform2D, Texture, UIElement> {
    public:
        DEFINE_NAME("UI System")

    private:
        const std::string m_font_path;
        SDL_FPoint m_previous_mouse_position = {0.0f, 0.0f};
        SDL_FPoint m_current_mouse_position = {0.0f, 0.0f};
        bool m_has_mouse_position_sample = false;

        bool DidMouseSweepThroughRect(const SDL_FRect &rect) const;

    public:
        TTF_Font *m_font = nullptr; // TODO: Find a better way to manage font resources

        UISystem(std::string font_path) : m_font_path(font_path), m_font(nullptr) {}
        ~UISystem();

        // System interface
        void OnStart() override;
        void OnEvent(SDL_Event &event) override;
        void OnWindowResize(SDL_Event &event) override;
        void OnUpdate() override;
        void OnRender() override;

    private:
        void SetupFont();

        void OnEventButton(EntityID entity);
        void OnEventSlider(EntityID entity);
        void OnEventDropdown(EntityID entity);
        void OnEventCheckbox(EntityID entity);
        void OnEventRadio(EntityID entity);

        void OnUpdateText(EntityID entity);
        void OnUpdateTextBox(EntityID entity);
        void OnUpdateImage(EntityID entity);
        void OnUpdateButton(EntityID entity);
        void OnUpdateSlider(EntityID entity);
        void OnUpdateDropdown(EntityID entity);
        void OnUpdateCheckbox(EntityID entity);
        void OnUpdateRadio(EntityID entity);

        void OnRenderText(EntityID entity);
        void OnRenderTextBox(EntityID entity);
        void OnRenderImage(EntityID entity);
        void OnRenderButton(EntityID entity);
        void OnRenderSlider(EntityID entity);
        void OnRenderDropdown(EntityID entity);
        void OnRenderCheckbox(EntityID entity);
        void OnRenderRadio(EntityID entity);
    };
} // namespace HBE::Default::Systems
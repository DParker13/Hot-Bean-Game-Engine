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

#include <HotBeanEngine/core/isystem.hpp>
#include <HotBeanEngine/defaults/components/miscellaneous/transform_2d.hpp>
#include <HotBeanEngine/defaults/components/rendering/texture.hpp>
#include <HotBeanEngine/defaults/components/ui/ui_element.hpp>

namespace HBE::Default::Systems {
    using HBE::Core::EntityID;
    using HBE::Default::Components::Transform2D;
    using HBE::Default::Components::Texture;
    using HBE::Default::Components::UIElement;
    
    /**
     * @brief Manages UI elements (Buttons, Checkboxes, etc).
     * Renders element to their texture and handles user interaction.
     */
    class UISystem : public HBE::Core::ISystem {
    public:
        REQUIRES_COMPONENTS(Transform2D, Texture, UIElement);
        DEFINE_NAME("UI System")

    private:
        const std::string _font_path;

    public:
        std::unordered_set<SDL_Keycode> _keysPressed;
        TTF_Font *m_font = nullptr; // This is not a good idea

        UISystem(std::string font_path) : _font_path(font_path), m_font(nullptr) {}
        ~UISystem();

        // System interface
        void OnStart() override;
        void OnWindowResize(SDL_Event &event) override;
        void OnUpdate() override;

    private:
        void SetupFont();
        void OnUpdateText(EntityID entity);
        void OnUpdateTextBox(EntityID entity);
        void OnUpdateImage(EntityID entity);
        void OnUpdateButton(EntityID entity);
        void OnUpdateSlider(EntityID entity);
        void OnUpdateDropdown(EntityID entity);
        void OnUpdateCheckbox(EntityID entity);
        void OnUpdateRadio(EntityID entity);
    };
} // namespace HBE::Default::Systems
/**
 * @file text_system.hpp
 * @author Daniel Parker (DParker13)
 * @brief System for text management
 * @version 0.1
 * @date 2026-03-17
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <unordered_set>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <HotBeanEngine/core/system.hpp>
#include <HotBeanEngine/defaults/components/miscellaneous/transform_2d.hpp>
#include <HotBeanEngine/defaults/components/rendering/texture.hpp>
#include <HotBeanEngine/defaults/components/ui/text.hpp>

namespace HBE::Default::Systems {
    using Components::Text;
    using Components::Texture;
    using Components::Transform2D;
    using Core::EntityID;

    /**
     * @brief Manages UI elements (Buttons, Checkboxes, etc).
     * Renders element to their texture and handles user interaction.
     */
    class TextSystem : public Core::GameSystem<Transform2D, Texture, Text> {
    public:
        DEFINE_NAME("Text System")

    private:
        const std::string m_font_path;

    public:
        TTF_Font *m_font = nullptr; // TODO: Find a better way to manage font resources

        TextSystem(std::string font_path) : m_font_path(font_path), m_font(nullptr) {}
        ~TextSystem();

        // System interface
        void OnStart() override;
        void OnWindowResize(SDL_Event &event) override;
        void OnRender() override;

    private:
        void SetupFont();
    };
} // namespace HBE::Default::Systems
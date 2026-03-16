/**
 * @file ui_rect.hpp
 * @author Daniel Parker
 * @brief UIRect component for screen-space UI positioning and layout.
 * @version 0.1
 * @date 2026-03-10
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <HotBeanEngine/core/all_core.hpp>
#include <HotBeanEngine/editor/iproperty_renderable.hpp>
#include <glm/glm.hpp>

namespace HBE::Default::Components {

    /**
     * @brief Screen-space UI positioning and layout component.
     *
     * Replaces Transform2D for UI elements that should remain fixed on screen.
     * Uses anchor and pivot points following game UI conventions (similar to Unity's RectTransform).
     *
     * Anchor point: Where on the screen the rect anchors to
     * Pivot point: Which point within the rect is used for positioning
     *
     * @example
     * @code
     *   // Center button horizontally at top of screen
     *   UIRect button_rect;
     *   button_rect.m_position = {0, 100};
     *   button_rect.m_size = {200, 50};
     *   button_rect.m_anchor = UIRect::AnchorPreset::TopCenter;
     *   button_rect.m_pivot = UIRect::PivotPreset::TopCenter;
     *   g_ecs.AddComponent<UIRect>(button_entity, button_rect);
     * @endcode
     */
    class UIRect : public Core::IComponent, public Core::DirtyFlag, public Application::GUI::IPropertyRenderable {
    public:
        /**
         * @enum AnchorPreset
         * @brief Anchoring position on screen
         *
         * Defines where the UI rect anchors relative to the screen.
         * Used as the reference point before applying position offset.
         */
        enum class AnchorPreset {
            TopLeft = 0,
            TopCenter = 1,
            TopRight = 2,
            CenterLeft = 3,
            Center = 4,
            CenterRight = 5,
            BottomLeft = 6,
            BottomCenter = 7,
            BottomRight = 8,
            Stretch = 9
        };

        /**
         * @enum PivotPreset
         * @brief Pivot point within the rect
         *
         * Defines which point within the rect's bounds is positioned at the anchor point.
         * For example, a Center pivot means the rect's center is placed at the anchor position.
         */
        enum class PivotPreset {
            TopLeft = 0,
            TopCenter = 1,
            TopRight = 2,
            CenterLeft = 3,
            Center = 4,
            CenterRight = 5,
            BottomLeft = 6,
            BottomCenter = 7,
            BottomRight = 8
        };

        /// Position offset in screen pixels from the anchor point
        glm::vec2 m_position = {0.0f, 0.0f};

        /// Size in screen pixels
        glm::vec2 m_size = {100.0f, 50.0f};

        /// Where on screen this rect anchors to
        AnchorPreset m_anchor = AnchorPreset::TopLeft;

        /// Which point within the rect is positioned at the anchor
        PivotPreset m_pivot = PivotPreset::TopLeft;

        /// Margins from anchor point (used for responsive positioning)
        float m_margin_left = 0.0f;
        float m_margin_right = 0.0f;
        float m_margin_top = 0.0f;
        float m_margin_bottom = 0.0f;

        DEFINE_NAME("UIRect");
        UIRect() = default;

        /**
         * @brief Calculate the actual screen position considering anchor and pivot.
         *
         * This gives you the top-left corner of the rect in screen coordinates.
         *
         * @param screen_width Screen width in pixels
         * @param screen_height Screen height in pixels
         * @return Top-left corner position in screen coordinates
         */
        glm::vec2 GetScreenPosition(int screen_width, int screen_height) const;

        /**
         * @brief Get the bounding rectangle in screen coordinates.
         *
         * @param screen_width Screen width in pixels
         * @param screen_height Screen height in pixels
         * @return SDL_FRect with position and size
         */
        SDL_FRect GetScreenBounds(int screen_width, int screen_height) const;

        void Serialize(YAML::Emitter &out) const override;
        void Deserialize(YAML::Node &node) override;
        void RenderProperties(int &id);

    private:
        /**
         * @brief Get the anchor position on screen based on m_anchor and margins.
         *
         * @param screen_width Screen width in pixels
         * @param screen_height Screen height in pixels
         * @return Screen position of the anchor point
         */
        glm::vec2 GetAnchorPosition(int screen_width, int screen_height) const;

        /**
         * @brief Get the pivot offset within the rect.
         *
         * This determines which point within the rect bounds is used as the positioning reference.
         *
         * @return Offset from top-left of rect to pivot point
         */
        glm::vec2 GetPivotOffset() const;
    };
} // namespace HBE::Default::Components

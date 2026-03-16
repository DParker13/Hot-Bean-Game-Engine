/**
 * @file ui_rect.hpp
 * @author Daniel Parker
 * @brief UIRect component for screen-space UI positioning and layout.
 * @version 0.1
 * @date 2026-03-10
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/defaults/components/ui/ui_rect.hpp>

#include <HotBeanEngine/editor/property_nodes/enum.hpp>
#include <HotBeanEngine/editor/property_nodes/float.hpp>
#include <HotBeanEngine/editor/property_nodes/vec2.hpp>

namespace HBE::Default::Components {
    using namespace Application::GUI::PropertyNodes;

    /**
     * @brief Calculate the actual screen position considering anchor and pivot.
     *
     * This gives you the top-left corner of the rect in screen coordinates.
     *
     * @param screen_width Screen width in pixels
     * @param screen_height Screen height in pixels
     * @return Top-left corner position in screen coordinates
     */
    glm::vec2 UIRect::GetScreenPosition(int screen_width, int screen_height) const {
        glm::vec2 anchor_pos = GetAnchorPosition(screen_width, screen_height);
        glm::vec2 pivot_offset = GetPivotOffset();
        return anchor_pos + m_position - pivot_offset;
    }

    /**
     * @brief Get the bounding rectangle in screen coordinates.
     *
     * @param screen_width Screen width in pixels
     * @param screen_height Screen height in pixels
     * @return SDL_FRect with position and size
     */
    SDL_FRect UIRect::GetScreenBounds(int screen_width, int screen_height) const {
        glm::vec2 screen_pos = GetScreenPosition(screen_width, screen_height);
        return SDL_FRect{screen_pos.x, screen_pos.y, m_size.x, m_size.y};
    }

    void UIRect::Serialize(YAML::Emitter &out) const {
        out << YAML::Key << "position" << YAML::Value << m_position;
        out << YAML::Key << "size" << YAML::Value << m_size;
        out << YAML::Key << "anchor" << YAML::Value << (int)m_anchor;
        out << YAML::Key << "pivot" << YAML::Value << (int)m_pivot;
        out << YAML::Key << "margin_left" << YAML::Value << m_margin_left;
        out << YAML::Key << "margin_right" << YAML::Value << m_margin_right;
        out << YAML::Key << "margin_top" << YAML::Value << m_margin_top;
        out << YAML::Key << "margin_bottom" << YAML::Value << m_margin_bottom;
    }

    void UIRect::Deserialize(YAML::Node &node) {
        if (node["position"])
            m_position = node["position"].as<glm::vec2>();
        if (node["size"])
            m_size = node["size"].as<glm::vec2>();
        if (node["anchor"])
            m_anchor = (AnchorPreset)node["anchor"].as<int>();
        if (node["pivot"])
            m_pivot = (PivotPreset)node["pivot"].as<int>();
        if (node["margin_left"])
            m_margin_left = node["margin_left"].as<float>();
        if (node["margin_right"])
            m_margin_right = node["margin_right"].as<float>();
        if (node["margin_top"])
            m_margin_top = node["margin_top"].as<float>();
        if (node["margin_bottom"])
            m_margin_bottom = node["margin_bottom"].as<float>();
        MarkDirty();
    }

    void UIRect::RenderProperties(int &id) {
        Vec2::RenderProperty(id, "Position", m_position, {-10000.0f, -10000.0f}, {10000.0f, 10000.0f});
        Vec2::RenderProperty(id, "Size", m_size, {0.0f, 0.0f}, {10000.0f, 10000.0f});

        Enum::RenderProperty<AnchorPreset>(id, "Anchor", m_anchor,
                                           {{AnchorPreset::TopLeft, "Top Left"},
                                            {AnchorPreset::TopCenter, "Top Center"},
                                            {AnchorPreset::TopRight, "Top Right"},
                                            {AnchorPreset::CenterLeft, "Center Left"},
                                            {AnchorPreset::Center, "Center"},
                                            {AnchorPreset::CenterRight, "Center Right"},
                                            {AnchorPreset::BottomLeft, "Bottom Left"},
                                            {AnchorPreset::BottomCenter, "Bottom Center"},
                                            {AnchorPreset::BottomRight, "Bottom Right"},
                                            {AnchorPreset::Stretch, "Stretch"}});

        Enum::RenderProperty<PivotPreset>(id, "Pivot", m_pivot,
                                          {{PivotPreset::TopLeft, "Top Left"},
                                           {PivotPreset::TopCenter, "Top Center"},
                                           {PivotPreset::TopRight, "Top Right"},
                                           {PivotPreset::CenterLeft, "Center Left"},
                                           {PivotPreset::Center, "Center"},
                                           {PivotPreset::CenterRight, "Center Right"},
                                           {PivotPreset::BottomLeft, "Bottom Left"},
                                           {PivotPreset::BottomCenter, "Bottom Center"},
                                           {PivotPreset::BottomRight, "Bottom Right"}});

        ImGui::Separator();
        ImGui::Text("Margins");
        Float::RenderProperty(id, "Left", m_margin_left, 0.0f);
        Float::RenderProperty(id, "Right", m_margin_right, 0.0f);
        Float::RenderProperty(id, "Top", m_margin_top, 0.0f);
        Float::RenderProperty(id, "Bottom", m_margin_bottom, 0.0f);
    }

    /**
     * @brief Get the anchor position on screen based on m_anchor and margins.
     *
     * @param screen_width Screen width in pixels
     * @param screen_height Screen height in pixels
     * @return Screen position of the anchor point
     */
    glm::vec2 UIRect::GetAnchorPosition(int screen_width, int screen_height) const {
        switch (m_anchor) {
        case AnchorPreset::TopLeft:
            return {m_margin_left, m_margin_top};
        case AnchorPreset::TopCenter:
            return {screen_width / 2.0f + m_margin_left, m_margin_top};
        case AnchorPreset::TopRight:
            return {(float)screen_width - m_margin_right, m_margin_top};
        case AnchorPreset::CenterLeft:
            return {m_margin_left, screen_height / 2.0f + m_margin_top};
        case AnchorPreset::Center:
            return {screen_width / 2.0f + m_margin_left, screen_height / 2.0f + m_margin_top};
        case AnchorPreset::CenterRight:
            return {(float)screen_width - m_margin_right, screen_height / 2.0f + m_margin_top};
        case AnchorPreset::BottomLeft:
            return {m_margin_left, (float)screen_height - m_margin_bottom};
        case AnchorPreset::BottomCenter:
            return {screen_width / 2.0f + m_margin_left, (float)screen_height - m_margin_bottom};
        case AnchorPreset::BottomRight:
            return {(float)screen_width - m_margin_right, (float)screen_height - m_margin_bottom};
        case AnchorPreset::Stretch:
            return {0.0f, 0.0f}; // Stretch mode handled separately
        default:
            return {0.0f, 0.0f};
        }
    }

    /**
     * @brief Get the pivot offset within the rect.
     *
     * This determines which point within the rect bounds is used as the positioning reference.
     *
     * @return Offset from top-left of rect to pivot point
     */
    glm::vec2 UIRect::GetPivotOffset() const {
        switch (m_pivot) {
        case PivotPreset::TopLeft:
            return {0.0f, 0.0f};
        case PivotPreset::TopCenter:
            return {m_size.x / 2.0f, 0.0f};
        case PivotPreset::TopRight:
            return {m_size.x, 0.0f};
        case PivotPreset::CenterLeft:
            return {0.0f, m_size.y / 2.0f};
        case PivotPreset::Center:
            return {m_size.x / 2.0f, m_size.y / 2.0f};
        case PivotPreset::CenterRight:
            return {m_size.x, m_size.y / 2.0f};
        case PivotPreset::BottomLeft:
            return {0.0f, m_size.y};
        case PivotPreset::BottomCenter:
            return {m_size.x / 2.0f, m_size.y};
        case PivotPreset::BottomRight:
            return {m_size.x, m_size.y};
        default:
            return {0.0f, 0.0f};
        }
    }

} // namespace HBE::Default::Components

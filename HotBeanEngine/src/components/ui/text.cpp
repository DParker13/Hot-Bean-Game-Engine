/**
 * @file text.cpp
 * @author Daniel Parker (DParker13)
 * @brief Used for storing font, text, and styling.
 * @version 0.1
 * @date 2026-03-15
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/components/ui/text.hpp>

#include <HotBeanEngine/editor/property_nodes/color.hpp>
#include <HotBeanEngine/editor/property_nodes/enum.hpp>
#include <HotBeanEngine/editor/property_nodes/int.hpp>
#include <HotBeanEngine/editor/property_nodes/string.hpp>

namespace HBE::Components {
    using namespace GUI::PropertyNodes;

    void Text::Deserialize(Core::IComponentReader &in) {
        if (in.Has("text")) {
            m_text = in.ReadString("text");
        }
        if (in.Has("foreground_color")) {
            m_foreground_color = in.ReadColor("foreground_color");
        }
        if (in.Has("background_color")) {
            m_background_color = in.ReadColor("background_color");
        }
        if (in.Has("size")) {
            m_size = in.ReadInt("size");
        }
        if (in.Has("style")) {
            m_style = in.ReadInt("style");
        }
        if (in.Has("wrapping_width")) {
            m_wrapping_width = in.ReadInt("wrapping_width");
        }
        MarkDirty();
    }

    void Text::Serialize(Core::IComponentWriter &out) const {
        if (!m_text.empty()) {
            out.Write("text", m_text);
        }
        out.Write("foreground_color", m_foreground_color);
        out.Write("background_color", m_background_color);
        out.Write("size", (int)m_size);
        out.Write("style", (int)m_style);
        out.Write("wrapping_width", (int)m_wrapping_width);
    }

    void Text::RenderProperties(int &id) {
        bool changed = false;

        changed |= String::RenderProperty(id, "Text", m_text);
        changed |= Color::RenderProperty(id, "Foreground Color", m_foreground_color);
        changed |= Color::RenderProperty(id, "Background Color", m_background_color);
        changed |= Enum::RenderProperty(id, "Font Style", m_style,
                                        {{TTF_STYLE_NORMAL, "Normal"},
                                         {TTF_STYLE_BOLD, "Bold"},
                                         {TTF_STYLE_ITALIC, "Italic"},
                                         {TTF_STYLE_UNDERLINE, "Underline"},
                                         {TTF_STYLE_STRIKETHROUGH, "Strikethrough"}});
        changed |= Int::RenderProperty(id, "Font Size", reinterpret_cast<int &>(m_size));
        changed |= Int::RenderProperty(id, "Wrapping Width", reinterpret_cast<int &>(m_wrapping_width));

        // Mark texture as dirty if any property changed
        if (changed) {
            MarkDirty();
        }
    }
} // namespace HBE::Components
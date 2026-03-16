/**
 * @file slider.cpp
 * @author Daniel Parker (DParker13)
 * @brief Slider component. Used for storing slider properties.
 * @version 0.1
 * @date 2026-03-15
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/defaults/components/ui/slider.hpp>

#include <HotBeanEngine/editor/property_nodes/color.hpp>
#include <HotBeanEngine/editor/property_nodes/enum.hpp>
#include <HotBeanEngine/editor/property_nodes/int.hpp>
#include <HotBeanEngine/editor/property_nodes/string.hpp>

namespace HBE::Default::Components {
    using namespace Application::GUI::PropertyNodes;

    void Slider::Deserialize(YAML::Node &node) {
        if (node["text"]) {
            m_text = node["text"].as<std::string>();
        }

        if (node["foreground_color"]) {
            m_foreground_color = node["foreground_color"].as<SDL_Color>();
        }

        if (node["background_color"]) {
            m_background_color = node["background_color"].as<SDL_Color>();
        }

        if (node["size"]) {
            m_size = node["size"].as<int>();
        }

        if (node["style"]) {
            m_style = node["style"].as<int>();
        }

        if (node["wrapping_width"]) {
            m_wrapping_width = node["wrapping_width"].as<int>();
        }
    }

    void Slider::Serialize(YAML::Emitter &out) const {
        if (!m_text.empty()) {
            out << YAML::Key << "text" << YAML::Value << m_text;
        }
        out << YAML::Key << "foreground_color" << YAML::Value << m_foreground_color;
        out << YAML::Key << "background_color" << YAML::Value << m_background_color;
        out << YAML::Key << "size" << YAML::Value << m_size;
        out << YAML::Key << "style" << YAML::Value << m_style;
        out << YAML::Key << "wrapping_width" << YAML::Value << m_wrapping_width;
    }

    /**
     * Gets the text of the Text component.
     *
     * This function gets the current text being rendered.
     *
     * @return The text being rendered.
     */
    std::string Slider::GetString() const { return m_text; }

    /**
     * Gets the C string representation of the text.
     *
     * This function is a convenience function that returns the C string representation of the text.
     * This is the same as calling GetString().c_str().
     *
     * @return A pointer to the C string representation of the text.
     */
    const char *Slider::GetChar() const { return m_text.data(); }

    void Slider::RenderProperties(int &id) {
        String::RenderProperty(id, "Text", m_text);
        Color::RenderProperty(id, "Foreground Color", m_foreground_color);
        Color::RenderProperty(id, "Background Color", m_background_color);
        Enum::RenderProperty(id, "Font Style", m_style,
                             {{TTF_STYLE_NORMAL, "Normal"},
                              {TTF_STYLE_BOLD, "Bold"},
                              {TTF_STYLE_ITALIC, "Italic"},
                              {TTF_STYLE_UNDERLINE, "Underline"},
                              {TTF_STYLE_STRIKETHROUGH, "Strikethrough"}});
        Int::RenderProperty(id, "Font Size", reinterpret_cast<int &>(m_size));
        Int::RenderProperty(id, "Wrapping Width", reinterpret_cast<int &>(m_wrapping_width));
    }
} // namespace HBE::Default::Components
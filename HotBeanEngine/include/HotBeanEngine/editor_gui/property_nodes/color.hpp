/**
 * @file color.hpp
 * @author Daniel Parker (DParker13)
 * @brief Color property node.
 * @version 0.1
 * @date 2025-10-19
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <imgui.h>

#include <HotBeanEngine/core.hpp>
#include <HotBeanEngine/editor_gui/property_nodes/iproperty_node.hpp>

namespace HBE::Application::GUI::PropertyNodes {
    struct Color : public IPropertyNode {
        static void RenderProperty(EntityID entity, std::string_view label, SDL_Color& value) {
            ImVec4 color = ImVec4(
                value.r / 255.0f,
                value.g / 255.0f,
                value.b / 255.0f,
                value.a / 255.0f
            );

            std::string unique_id = std::string(label) + std::to_string(entity);
            ImGui::PushID(unique_id.c_str());
            ImGui::Text("%s", label.data());
            ImGui::SameLine();
            ImGui::PushItemWidth(50.0f);
            ImGui::ColorButton(label.data(), color, ImGuiColorEditFlags_DefaultOptions_);
            ImGui::PopID();

            value.r = static_cast<Uint8>(color.x * 255.0f);
            value.g = static_cast<Uint8>(color.y * 255.0f);
            value.b = static_cast<Uint8>(color.z * 255.0f);
            value.a = static_cast<Uint8>(color.w * 255.0f);
        }
    };
}
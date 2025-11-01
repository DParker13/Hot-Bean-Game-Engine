/**
 * @file vec2.hpp
 * @author Daniel Parker (DParker13)
 * @brief Vector 2 property node.
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
    struct Vec2 : public IPropertyNode {
        static void RenderProperty(EntityID entity, std::string_view label, glm::vec2& values) {
            std::string unique_id = std::string(label) + std::to_string(entity);
            ImGui::PushID(unique_id.c_str());
            ImGui::Text("%s", label.data());
            ImGui::SameLine();
            ImGui::PushItemWidth(50.0f);
            ImGui::Text("X");
            ImGui::SameLine();
            ImGui::DragFloat(("##" + unique_id + "_X").c_str(), &values.x, 0.1f);
            ImGui::PopItemWidth();
            ImGui::SameLine();
            ImGui::Text("Y");
            ImGui::SameLine();
            ImGui::PushItemWidth(50.0f);
            ImGui::DragFloat(("##" + unique_id + "_Y").c_str(), &values.y, 0.1f);
            ImGui::PopItemWidth();
            ImGui::PopID();
        }
    };
}
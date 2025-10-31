/**
 * @file vec3.hpp
 * @author Daniel Parker (DParker13)
 * @brief Vector 3 property node.
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
    struct Vec3 : public IPropertyNode {
        static void RenderProperty(Entity& entity, std::string_view label, glm::vec3& values) {
            std::string unique_id = std::string(label) + std::to_string(entity);
            ImGui::PushID(unique_id.c_str());
            ImGui::Text("%s", label.data());
            ImGui::SameLine();
            ImGui::Text("X##1");
            ImGui::SameLine();
            ImGui::PushItemWidth(50.0f);
            ImGui::DragFloat("", &values.x, 0.1f);
            ImGui::PopItemWidth();
            ImGui::Text("Y##2");
            ImGui::SameLine();
            ImGui::PushItemWidth(50.0f);
            ImGui::DragFloat("", &values.y, 0.1f);
            ImGui::PopItemWidth();
            ImGui::Text("Z##3");
            ImGui::SameLine();
            ImGui::PushItemWidth(50.0f);
            ImGui::DragFloat("", &values.z, 0.1f);
            ImGui::PopItemWidth();
            ImGui::PopID();
        }
    };
}
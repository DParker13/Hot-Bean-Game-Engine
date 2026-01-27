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

#include <HotBeanEngine/core/all_core.hpp>

namespace HBE::Application::GUI::PropertyNodes {
    using namespace HBE::Core;

    struct Vec3 {
        static bool RenderProperty(int& id, std::string_view label, glm::vec3& values,
            glm::vec3 min = glm::vec3(-FLT_MAX), glm::vec3 max = glm::vec3(FLT_MAX), bool disabled = false) {
            ImGui::PushID(id++);
            ImGui::Text("%s", label.data());
            ImGui::SameLine();
            ImGui::Text("X##1");
            ImGui::SameLine();
            ImGui::PushItemWidth(50.0f);
            ImGui::BeginDisabled(disabled);
            bool changed_x = ImGui::DragFloat("", &values.x, 0.1f, min.x, max.x);
            ImGui::EndDisabled();
            ImGui::PopItemWidth();
            ImGui::Text("Y##2");
            ImGui::SameLine();
            ImGui::PushItemWidth(50.0f);
            ImGui::BeginDisabled(disabled);
            bool changed_y = ImGui::DragFloat("", &values.y, 0.1f, min.y, max.y);
            ImGui::EndDisabled();
            ImGui::PopItemWidth();
            ImGui::Text("Z##3");
            ImGui::SameLine();
            ImGui::PushItemWidth(50.0f);
            ImGui::BeginDisabled(disabled);
            bool changed_z = ImGui::DragFloat("", &values.z, 0.1f, min.z, max.z);
            ImGui::EndDisabled();
            ImGui::PopItemWidth();
            ImGui::PopID();
            
            return changed_x || changed_y || changed_z;
        }
    };
}
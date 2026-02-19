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

#include <HotBeanEngine/core/all_core.hpp>

namespace HBE::Application::GUI::PropertyNodes {

    struct Vec2 {
        static bool RenderProperty(int &id, std::string_view label, glm::vec2 &values,
                                   glm::vec2 min = glm::vec2(-FLT_MAX), glm::vec2 max = glm::vec2(FLT_MAX),
                                   bool disabled = false) {
            ImGui::PushID(id++);
            ImGui::Text("%s", label.data());
            ImGui::SameLine();
            ImGui::Text("X");
            ImGui::SameLine();
            ImGui::PushItemWidth(50.0f);
            ImGui::BeginDisabled(disabled);
            bool changed_x =
                ImGui::DragFloat(("##" + std::to_string(id) + "_X").c_str(), &values.x, 0.1f, min.x, max.x);
            ImGui::EndDisabled();
            ImGui::PopItemWidth();
            ImGui::SameLine();
            ImGui::Text("Y");
            ImGui::SameLine();
            ImGui::PushItemWidth(50.0f);
            ImGui::BeginDisabled(disabled);
            bool changed_y =
                ImGui::DragFloat(("##" + std::to_string(id) + "_Y").c_str(), &values.y, 0.1f, min.y, max.y);
            ImGui::EndDisabled();
            ImGui::PopItemWidth();
            ImGui::PopID();

            return changed_x || changed_y;
        }
    };
} // namespace HBE::Application::GUI::PropertyNodes
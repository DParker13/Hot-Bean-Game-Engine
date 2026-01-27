/**
 * @file int.hpp
 * @author Daniel Parker (DParker13)
 * @brief Integer property node.
 * @version 0.1
 * @date 2025-10-19
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <imgui.h>
#include <string>

namespace HBE::Application::GUI::PropertyNodes {
    struct Int {
        static bool RenderProperty(int& id, std::string_view label, int& value,
            int min = INT_MIN, int max = INT_MAX, bool disabled = false) {
            ImGui::PushID(id++);
            ImGui::Text("%s", label.data());
            ImGui::SameLine();
            ImGui::PushItemWidth(50.0f);
            ImGui::BeginDisabled(disabled);
            bool changed = ImGui::DragInt("", &value, 1, min, max);
            ImGui::EndDisabled();
            ImGui::PopItemWidth();
            ImGui::PopID();
            
            return changed;
        }
    };
}
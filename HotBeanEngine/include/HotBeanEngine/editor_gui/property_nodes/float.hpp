/**
 * @file float.hpp
 * @author Daniel Parker (DParker13)
 * @brief Float property node.
 * @version 0.1
 * @date 2025-10-19
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <imgui.h>
#include <string>

namespace HBE::Application::GUI::PropertyNodes {
    struct Float {
        static bool RenderProperty(int& id, std::string_view label, float& value,
            float min = -FLT_MAX, float max = FLT_MAX, bool disabled = false) {
            ImGui::PushID(id++);
            ImGui::Text("%s", label.data());
            ImGui::SameLine();
            ImGui::PushItemWidth(50.0f);
            ImGui::BeginDisabled(disabled);
            bool changed = ImGui::DragFloat("", &value, 0.1f, min, max, "%.3f", ImGuiSliderFlags_AlwaysClamp);
            ImGui::EndDisabled();
            ImGui::PopItemWidth();
            ImGui::PopID();
            
            return changed;
        }
    };
}
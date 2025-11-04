/**
 * @file string.hpp
 * @author Daniel Parker (DParker13)
 * @brief String property node.
 * @version 0.1
 * @date 2025-10-19
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <imgui.h>
#include <string>

namespace HBE::Application::GUI::PropertyNodes {
    
    struct String {
        static bool RenderProperty(int& id, std::string_view label, std::string& value, bool disabled = false) {
            ImGui::PushID(id++);
            ImGui::Text("%s", label.data());
            ImGui::SameLine();
            ImGui::PushItemWidth(50.0f);
            ImGui::BeginDisabled(disabled);
            bool changed = ImGui::InputTextMultiline("", value.data(), value.size());
            ImGui::EndDisabled();
            ImGui::PopItemWidth();
            ImGui::PopID();
            return changed;
        }
    };
}
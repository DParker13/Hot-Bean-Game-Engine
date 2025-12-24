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
        static bool RenderProperty(int& id, std::string_view label, std::string& value, bool disabled = false, bool isMultiline = false) {
            ImGui::PushID(id++);
            ImGui::Text("%s", label.data());
            ImGui::SameLine();
            ImGui::BeginDisabled(disabled);

            bool changed = false;
            float width = ImGui::GetContentRegionAvail().x;
            if (isMultiline) {
                changed = ImGui::InputTextMultiline("", value.data(), value.size(), ImVec2(width, ImGui::GetTextLineHeight() * 4));
            }
            else {
                changed = ImGui::InputText("", value.data(), value.size());
            }
            ImGui::EndDisabled();
            ImGui::PopID();
            return changed;
        }
    };
}
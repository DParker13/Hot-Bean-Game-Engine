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

#include <HotBeanEngine/core/all_core.hpp>

namespace HBE::Application::GUI::PropertyNodes {

    struct Color {
        static bool RenderProperty(int &id, std::string_view label, SDL_Color &value, bool disabled = false) {
            ImVec4 color = ImVec4(value.r / 255.0f, value.g / 255.0f, value.b / 255.0f, value.a / 255.0f);

            ImGui::PushID(id++);
            ImGui::Text("%s", label.data());
            ImGui::SameLine();
            ImGui::PushItemWidth(150.0f);
            ImGui::BeginDisabled(disabled);
            bool changed = ImGui::ColorEdit4(label.data(), &color.x, ImGuiColorEditFlags_DefaultOptions_);
            ImGui::EndDisabled();
            ImGui::PopItemWidth();
            ImGui::PopID();

            if (changed) {
                value.r = static_cast<Uint8>(color.x * 255.0f);
                value.g = static_cast<Uint8>(color.y * 255.0f);
                value.b = static_cast<Uint8>(color.z * 255.0f);
                value.a = static_cast<Uint8>(color.w * 255.0f);
            }

            return changed;
        }
    };
} // namespace HBE::Application::GUI::PropertyNodes
/**
 * @file color.hpp
 * @author Daniel Parker (DParker13)
 * @brief Color property node.
 * @version 0.1
 * @date 2025-10-20
 *
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <imgui.h>

#include <HotBeanEngine/core/all_core.hpp>

namespace HBE::Application::GUI::PropertyNodes {
    struct Enum {
        template <typename EnumType>
        static bool RenderProperty(int &id, std::string_view label, EnumType &value,
                                   const std::vector<std::pair<EnumType, std::string>> &options,
                                   bool disabled = false) {
            ImGui::PushID(id++);
            ImGui::Text("%s", label.data());
            ImGui::SameLine();
            ImGui::PushItemWidth(100.0f);
            ImGui::BeginDisabled(disabled);

            // Find current index
            int current_index = 0;
            for (size_t i = 0; i < options.size(); ++i) {
                if (options[i].first == value) {
                    current_index = static_cast<int>(i);
                    break;
                }
            }

            // Build items array
            std::vector<const char *> items;
            for (const auto &opt : options) {
                items.push_back(opt.second.c_str());
            }

            bool changed = false;
            if (ImGui::Combo("", &current_index, items.data(), static_cast<int>(items.size()))) {
                value = options[current_index].first;
                changed = true;
            }

            ImGui::EndDisabled();
            ImGui::PopItemWidth();
            ImGui::PopID();
            return changed;
        }
    };
} // namespace HBE::Application::GUI::PropertyNodes
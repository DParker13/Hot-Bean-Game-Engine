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

#include <HotBeanEngine/core.hpp>
#include <HotBeanEngine/editor_gui/property_nodes/iproperty_node.hpp>

namespace HBE::Application::GUI::PropertyNodes {
    struct Enum : public IPropertyNode {
        template<typename EnumType>
        static void RenderProperty(Entity& entity, std::string_view label, EnumType& value, const std::vector<std::pair<EnumType, std::string>>& options) {
            static_assert(std::is_enum_v<EnumType>, "EnumType must be an enum");

            std::string unique_id = std::string(label) + std::to_string(entity);
            ImGui::PushID(unique_id.c_str());
            ImGui::Text("%s", label.data());
            ImGui::SameLine();
            ImGui::PushItemWidth(50.0f);

            // Find current index
            int current_index = 0;
            for (size_t i = 0; i < options.size(); ++i) {
                if (options[i].first == value) {
                    current_index = static_cast<int>(i);
                    break;
                }
            }

            // Build items array
            std::vector<const char*> items;
            for (const auto& opt : options) {
                items.push_back(opt.second.c_str());
            }

            if (ImGui::Combo("", &current_index, items.data(), static_cast<int>(items.size()))) {
                value = options[current_index].first;
            }

            ImGui::PopID();
        }
    };
}
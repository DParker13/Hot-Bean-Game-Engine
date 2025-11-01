/**
 * @file bool.hpp
 * @author Daniel Parker (DParker13)
 * @brief Boolean property node.
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
    struct Bool : public IPropertyNode {
        static void RenderProperty(EntityID entity, std::string_view label, bool& value) {
            std::string unique_id = std::string(label) + std::to_string(entity);
            ImGui::PushID(unique_id.c_str());
            ImGui::Text("%s", label.data());
            ImGui::SameLine();
            ImGui::PushItemWidth(50.0f);
            ImGui::Checkbox("", &value);
            ImGui::PopID();
        }
    };
}
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

#include <HotBeanEngine/core.hpp>
#include <HotBeanEngine/editor_gui/property_nodes/iproperty_node.hpp>

namespace HBE::Application::GUI::PropertyNodes {
    struct Int : public IPropertyNode {
        static void RenderProperty(Entity& entity, std::string_view label, int& value) {
            std::string unique_id = std::string(label) + std::to_string(entity);
            ImGui::PushID(unique_id.c_str());
            ImGui::Text("%s", label.data());
            ImGui::SameLine();
            ImGui::PushItemWidth(50.0f);
            ImGui::DragInt("", &value, 1);
            ImGui::PopID();
        }
    };
}
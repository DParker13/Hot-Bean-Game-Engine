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

#include <HotBeanEngine/core.hpp>
#include <HotBeanEngine/editor_gui/property_nodes/iproperty_node.hpp>

namespace HBE::Application::GUI::PropertyNodes {
    struct Float : public IPropertyNode {
        static void RenderProperty(Entity& entity, std::string_view label, float& value) {
            std::string unique_id = std::string(label) + std::to_string(entity);
            ImGui::PushID(unique_id.c_str());
            ImGui::Text("%s", label.data());
            ImGui::SameLine();
            ImGui::PushItemWidth(50.0f);
            ImGui::DragFloat("", &value, 0.1f, ImGuiSliderFlags_AlwaysClamp);
            ImGui::PopID();
        }
    };
}
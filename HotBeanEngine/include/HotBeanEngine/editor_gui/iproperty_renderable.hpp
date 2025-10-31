/**
 * @file iproperty_renderable.hpp
 * @author Daniel Parker (DParker13)
 * @brief Interface for components that can be rendered in the editor GUI.
 * @version 0.1
 * @date 2025-10-26
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <imgui.h>
#include <functional>

#include <HotBeanEngine/core.hpp>

namespace HBE::Application::GUI {
    struct IPropertyRenderable {
        virtual void RenderProperties(HBE::Core::Entity entity, HBE::Core::Component* component) = 0;
    };

    template<typename T>
    static void RenderProperties(HBE::Core::Entity entity, HBE::Core::Component* component, std::function<void(HBE::Core::Entity, T*)> renderPropertiesFunc) {
        static_assert(std::is_base_of_v<HBE::Core::Component, T> && "T must inherit from Component");
        static_assert(has_static_get_name<T>::value && "T must have a StaticGetName() function");

        auto* typed = dynamic_cast<T*>(component);
        if (!typed) {
            return;
        }

        if (ImGui::CollapsingHeader((std::string(T::StaticGetName()) + " Component").c_str())) {
            renderPropertiesFunc(entity, typed);
        }
    }
}
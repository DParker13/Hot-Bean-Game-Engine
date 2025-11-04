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

#include <HotBeanEngine/core/all_core.hpp>

namespace HBE::Application::GUI {
    using namespace HBE::Core;

    struct IPropertyRenderable {
        virtual void RenderProperties(int& id, EntityID entity) = 0;
    };
}
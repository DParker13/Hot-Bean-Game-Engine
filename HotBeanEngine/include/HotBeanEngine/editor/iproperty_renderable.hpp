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

namespace HBE::Application::GUI {
    struct IPropertyRenderable {
        virtual void RenderProperties(int& id) = 0;
    };
}
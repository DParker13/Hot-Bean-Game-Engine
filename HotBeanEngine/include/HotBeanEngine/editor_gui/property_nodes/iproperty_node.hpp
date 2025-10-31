/**
 * @file property_node.hpp
 * @author Daniel Parker (DParker13)
 * @brief Property node interface.
 * @version 0.1
 * @date 2025-10-19
 * 
 * @copyright Copyright (c) 2025
 */

#pragma once

namespace HBE::Application::GUI::PropertyNodes {
    struct IPropertyNode {
        virtual ~IPropertyNode() = default;
        virtual void RenderProperty() = 0;
    };
}
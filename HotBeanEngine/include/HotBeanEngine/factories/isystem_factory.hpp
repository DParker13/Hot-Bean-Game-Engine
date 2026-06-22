/**
 * @file isystem_factory.hpp
 * @author Daniel Parker (DParker13)
 * @brief Interface for system factory.
 * @version 0.1
 * @date 2026-06-22
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

namespace HBE::Factories {
    class ISystemFactory {
    public:
        virtual void RegisterSystems() = 0;
    };
} // namespace HBE::Factories
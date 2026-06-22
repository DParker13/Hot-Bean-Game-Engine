/**
 * @file system_factory.hpp
 * @author Daniel Parker (DParker13)
 * @brief Concrete implementation of the system factory interface.
 * @version 0.1
 * @date 2026-06-22
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <HotBeanEngine/factories/isystem_factory.hpp>

namespace HBE::Factories {
    class SystemFactory : public ISystemFactory {
    public:
        virtual void RegisterSystems() override;
    };
} // namespace HBE::Factories
#pragma once

#include <HotBeanEngine/application/isystem_factory.hpp>

namespace HBE::Application {
    class SystemFactory : public ISystemFactory {
    public:
        virtual void RegisterSystems() override;
    };
} // namespace HBE::Application
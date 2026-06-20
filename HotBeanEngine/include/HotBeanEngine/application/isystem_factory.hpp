#pragma once

namespace HBE::Application {
    class ISystemFactory {
    public:
        virtual void RegisterSystems() = 0;
    };
} // namespace HBE::Application
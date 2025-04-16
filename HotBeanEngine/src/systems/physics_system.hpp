#pragma once

#include <core.hpp>

#include "../components/transform_2d.hpp"
#include "../components/rigidbody.hpp"

using namespace Components;
using namespace Core::Application;
using namespace Core::ECS;

namespace Systems {
    class PhysicsSystem : public System {
        public:
            PhysicsSystem(App& app);

            //System interface
            void OnUpdate() override;

            std::string ToString() const;
    };
}
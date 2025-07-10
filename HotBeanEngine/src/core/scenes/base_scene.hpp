#pragma once

#include "../application/all_application.hpp"
#include "../systems/all_systems.hpp"

using namespace Core::Systems;

namespace Core::Application {
    class BaseScene : public Scene {
        public:
            BaseScene(std::string name, std::string scene_path) : Scene(name, scene_path) {}

            /**
             * @brief Initializes the default systems needed for basic game functionality.
             * The order each system is initialized is important! That is the order they are then called.
             */
            void SetupSystems() override;

        protected:

            /**
             * @brief Registers a system with the ECSManager
             * 
             * @tparam System Class that inherits from System to be registered
             * @tparam Args Types of arguments to be passed to the system
             * @param args Arguments to be passed to the system
             * @return System& Reference to the registered system
             */
            template <typename System, typename... Args>
            System& RegisterSystem(Args&&... args) {
                return App::GetInstance().GetECSManager()->RegisterSystem<System, Args&&...>(std::forward<Args>(args)...);
            }
    };
}
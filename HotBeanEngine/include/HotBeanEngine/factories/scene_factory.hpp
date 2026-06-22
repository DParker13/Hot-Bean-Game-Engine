/**
 * @file scene_factory.hpp
 * @author Daniel Parker (DParker13)
 * @brief Implementation for scene factory.
 * @version 0.1
 * @date 2026-06-22
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <HotBeanEngine/factories/iscene_factory.hpp>

namespace HBE::Factories {
    class SceneFactory : public ISceneFactory {
    public:
        void RegisterScenes() override;
    };
} // namespace HBE::Factories
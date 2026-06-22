/**
 * @file iscene_factory.hpp
 * @author Daniel Parker (DParker13)
 * @brief Interface for scene factory.
 * @version 0.1
 * @date 2026-06-22
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

namespace HBE::Factories {
    class ISceneFactory {
    public:
        virtual void RegisterScenes() = 0;
    };
} // namespace HBE::Factories
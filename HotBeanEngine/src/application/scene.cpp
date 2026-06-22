/**
 * @file scene.cpp
 * @author Daniel Parker (DParker13)
 * @brief Default scene implementation. Sets up default systems for a basic game scene.
 * @version 0.1
 * @date 2025-12-24
 *
 * @copyright Copyright (c) 2025
 */

#include <HotBeanEngine/application/scene.hpp>

namespace HBE::Application {
    void Scene::SetupScene() {}

    void Scene::Serialize(Core::ISerializationWriter &out) const { out.Write("Name", m_name); }

    void Scene::Deserialize(Core::ISerializationReader &in) { m_name = in.ReadString("Name"); }
} // namespace HBE::Application
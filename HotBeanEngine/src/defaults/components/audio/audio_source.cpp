/**
 * @file audio_source.cpp
 * @author Daniel Parker (DParker13)
 * @brief Audio Source component. Used to play audio files.
 * @version 0.1
 * @date 2026-03-15
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/defaults/components/audio/audio_source.hpp>

namespace HBE::Default::Components {
    void AudioSource::Serialize(YAML::Emitter &out) const { out << YAML::Key << "path" << YAML::Value << path; }

    void AudioSource::Deserialize(YAML::Node &node) { path = node["path"].as<std::string>(); }
} // namespace HBE::Default::Components
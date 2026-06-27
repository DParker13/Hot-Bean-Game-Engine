/**
 * @file audio_source.cpp
 * @author Daniel Parker (DParker13)
 * @brief Audio Source component. Used to play audio files.
 * @version 0.1
 * @date 2026-03-15
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/components/audio/audio_source.hpp>

namespace HBE::Components {
    void AudioSource::Serialize(Core::ISerializationWriter &out) const { out.Write("path", m_path); }

    void AudioSource::Deserialize(Core::ISerializationReader &in) { in.Read("path", m_path); }
} // namespace HBE::Components
/**
 * @file yaml_serialization_writer.hpp
 * @author Daniel Parker (DParker13)
 * @brief YAML-backed implementations of ISerializationWriter.
 * @version 0.1
 * @date 2026-06-19
 *
 * @copyright Copyright (c) 2026
 */

#pragma once

#include <functional>
#include <utility>

#include <HotBeanEngine/core/iserialization_writer.hpp>
#include <yaml-cpp/yaml.h>

namespace HBE::Serializers {
    /// @brief Writes component data to a YAML::Emitter.
    class YamlWriter : public Core::ISerializationWriter {
    private:
        YAML::Emitter &m_out;

    public:
        explicit YamlWriter(YAML::Emitter &out) : m_out(out) {}

        template <typename T>
        YamlWriter &operator<<(T &&value) {
            m_out << std::forward<T>(value);
            return *this;
        }

        void WriteToFile(const std::filesystem::path &filepath,
                         Core::ISerializationWriter::FileWriteMode mode =
                             Core::ISerializationWriter::FileWriteMode::Overwrite) const override;

        void Write(const std::string &key, bool value) override;
        void Write(const std::string &key, int value) override;
        void Write(const std::string &key, float value) override;
        void Write(const std::string &key, const std::string &value) override;
        void Write(const std::string &key, uint8_t value) override;
        void Write(const std::string &key, uint32_t value) override;
        void Write(const std::string &key, int64_t value) override;
        void Write(const std::string &key, glm::vec2 value) override;
        void Write(const std::string &key, const SDL_Color &value) override;
        void Write(const std::string &key, const std::filesystem::path &value) override;
        void Write(const std::string &key, const std::vector<std::string> &value) override;
        void Write(const std::string &key, const std::vector<std::filesystem::path> &value) override;

        void BeginSection(const std::string &key) override;
        void WriteEmptySection(const std::string &key) override;
        void EndSection() override;
        void WriteComment(const std::string &text) override;
    };
} // namespace HBE::Serializers

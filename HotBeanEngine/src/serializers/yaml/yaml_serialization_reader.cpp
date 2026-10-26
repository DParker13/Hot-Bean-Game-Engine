/**
 * @file yaml_serialization_reader.cpp
 * @author Daniel Parker (DParker13)
 * @brief YAML-backed implementations of ISerializationReader.
 * @version 0.1
 * @date 2026-06-19
 *
 * @copyright Copyright (c) 2026
 */

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/serializers/yaml/yaml_extensions.hpp>
#include <HotBeanEngine/serializers/yaml/yaml_serialization_reader.hpp>

namespace HBE::Serializers {
    namespace {
        void LogYamlReadError(std::string_view key, const std::string &type_name, const YAML::Exception &e) {
            LOG(Core::LoggingType::ERROR,
                "YamlReader failed to read key '" + std::string(key) + "' as " + type_name + ": " + e.what());
        }

        template <typename TValue>
        bool TryReadAs(const YAML::Node &node, std::string_view key, const std::string &type_name, TValue &value) {
            try {
                const YAML::Node value_node = node[std::string(key)];
                if (!value_node.IsDefined()) {
                    return false;
                }

                value = value_node.as<TValue>();
                return true;
            } catch (const YAML::Exception &e) {
                LogYamlReadError(key, type_name, e);
            }

            return false;
        }
    } // namespace

    void YamlReader::BeginSection(std::string_view key) {
        m_stack.push_back(m_node);
        // Rebind the handle without modifying nodes shared with other readers or iterators.
        m_node.reset(m_node[std::string(key)]);
    }

    void YamlReader::EndSection() {
        if (!m_stack.empty()) {
            m_node.reset(m_stack.back());
            m_stack.pop_back();
        }
    }

    bool YamlReader::Has(std::string_view key) const { return m_node[std::string(key)].IsDefined(); }

    void YamlReader::Read(std::string_view key, bool &value) const { TryReadAs(m_node, key, "bool", value); }
    void YamlReader::Read(std::string_view key, int &value) const { TryReadAs(m_node, key, "int", value); }
    void YamlReader::Read(std::string_view key, float &value) const { TryReadAs(m_node, key, "float", value); }
    void YamlReader::Read(std::string_view key, std::string &value) const { TryReadAs(m_node, key, "string", value); }
    void YamlReader::Read(std::string_view key, uint8_t &value) const {
        int raw_value = 0;
        if (TryReadAs(m_node, key, "uint8_t", raw_value)) {
            value = static_cast<uint8_t>(raw_value);
        }
    }
    void YamlReader::Read(std::string_view key, uint32_t &value) const { TryReadAs(m_node, key, "uint32_t", value); }
    void YamlReader::Read(std::string_view key, int64_t &value) const {
        int raw_value = 0;
        if (TryReadAs(m_node, key, "int64_t", raw_value)) {
            value = static_cast<int64_t>(raw_value);
        }
    }
    void YamlReader::Read(std::string_view key, glm::vec2 &value) const { TryReadAs(m_node, key, "glm::vec2", value); }
    void YamlReader::Read(std::string_view key, SDL_Color &value) const { TryReadAs(m_node, key, "SDL_Color", value); }
    void YamlReader::Read(std::string_view key, std::filesystem::path &value) const {
        TryReadAs(m_node, key, "std::filesystem::path", value);
    }
    void YamlReader::Read(std::string_view key, std::vector<std::string> &value) const {
        try {
            const YAML::Node arrayNode = key.empty() ? m_node : m_node[std::string(key)];
            if (!arrayNode.IsSequence()) {
                return;
            }

            value.clear();
            for (const auto &item : arrayNode) {
                value.push_back(item.as<std::string>());
            }
        } catch (const YAML::Exception &e) {
            LogYamlReadError(key, "std::vector<std::string>", e);
        }
    }

    void YamlReader::Read(std::string_view key, std::vector<std::filesystem::path> &value) const {
        try {
            const YAML::Node arrayNode = key.empty() ? m_node : m_node[std::string(key)];
            if (!arrayNode.IsSequence()) {
                return;
            }

            value.clear();
            for (const auto &item : arrayNode) {
                value.push_back(std::filesystem::path(item.as<std::string>()));
            }
        } catch (const YAML::Exception &e) {
            LogYamlReadError(key, "std::vector<std::filesystem::path>", e);
        }
    }

    size_t YamlReader::Size() const { return m_node.size(); }

} // namespace HBE::Serializers

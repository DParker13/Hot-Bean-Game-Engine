#include <HotBeanEngine/serializers/binary/binary_serialization_writer.hpp>

namespace HBE::Serializers {

    void BinaryComponentWriter::Write(std::string_view key, bool value) {
        m_fields.push_back({std::string(key), FieldType::Bool, value});
    }
    void BinaryComponentWriter::Write(std::string_view key, int value) {
        m_fields.push_back({std::string(key), FieldType::Int, value});
    }
    void BinaryComponentWriter::Write(std::string_view key, float value) {
        m_fields.push_back({std::string(key), FieldType::Float, value});
    }
    void BinaryComponentWriter::Write(std::string_view key, std::string_view value) {
        m_fields.push_back({std::string(key), FieldType::String, std::string(value)});
    }
    void BinaryComponentWriter::Write(std::string_view key, std::string value) {
        m_fields.push_back({std::string(key), FieldType::String, std::move(value)});
    }
    void BinaryComponentWriter::Write(std::string_view key, uint8_t value) {
        m_fields.push_back({std::string(key), FieldType::Uint8, value});
    }
    void BinaryComponentWriter::Write(std::string_view key, uint32_t value) {
        m_fields.push_back({std::string(key), FieldType::Uint32, value});
    }
    void BinaryComponentWriter::Write(std::string_view key, int64_t value) {
        m_fields.push_back({std::string(key), FieldType::Int64, value});
    }
    void BinaryComponentWriter::Write(std::string_view key, glm::vec2 value) {
        m_fields.push_back({std::string(key), FieldType::Vec2, value});
    }
    void BinaryComponentWriter::Write(std::string_view key, const SDL_Color &value) {
        m_fields.push_back({std::string(key), FieldType::Color, value});
    }
    void BinaryComponentWriter::Write(std::string_view key, const std::filesystem::path &value) {
        m_fields.push_back({std::string(key), FieldType::Path, value});
    }
    void BinaryComponentWriter::Write(std::string_view key, const std::vector<std::string> &value) {
        m_fields.push_back({std::string(key), FieldType::VecString, value});
    }
    void BinaryComponentWriter::Write(std::string_view key, const std::vector<std::filesystem::path> &value) {
        m_fields.push_back({std::string(key), FieldType::VecPath, value});
    }

} // namespace HBE::Serializers

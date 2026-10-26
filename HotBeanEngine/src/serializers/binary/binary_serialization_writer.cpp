#include <HotBeanEngine/serializers/binary/binary_serialization_writer.hpp>

namespace HBE::Serializers {

    void BinaryWriter::Write(const std::string &key, bool value) { m_fields.push_back({key, FieldType::Bool, value}); }
    void BinaryWriter::Write(const std::string &key, int value) { m_fields.push_back({key, FieldType::Int, value}); }
    void BinaryWriter::Write(const std::string &key, float value) {
        m_fields.push_back({key, FieldType::Float, value});
    }
    void BinaryWriter::Write(const std::string &key, const std::string &value) {
        m_fields.push_back({key, FieldType::String, value});
    }
    void BinaryWriter::Write(const std::string &key, uint8_t value) {
        m_fields.push_back({key, FieldType::Uint8, value});
    }
    void BinaryWriter::Write(const std::string &key, uint32_t value) {
        m_fields.push_back({key, FieldType::Uint32, value});
    }
    void BinaryWriter::Write(const std::string &key, int64_t value) {
        m_fields.push_back({key, FieldType::Int64, value});
    }
    void BinaryWriter::Write(const std::string &key, glm::vec2 value) {
        m_fields.push_back({key, FieldType::Vec2, value});
    }
    void BinaryWriter::Write(const std::string &key, const SDL_Color &value) {
        m_fields.push_back({key, FieldType::Color, value});
    }
    void BinaryWriter::Write(const std::string &key, const std::filesystem::path &value) {
        m_fields.push_back({key, FieldType::Path, value});
    }
    void BinaryWriter::Write(const std::string &key, const std::vector<std::string> &value) {
        m_fields.push_back({key, FieldType::VecString, value});
    }
    void BinaryWriter::Write(const std::string &key, const std::vector<std::filesystem::path> &value) {
        m_fields.push_back({key, FieldType::VecPath, value});
    }

} // namespace HBE::Serializers

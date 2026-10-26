#include <HotBeanEngine/serializers/binary/binary_serialization_reader.hpp>

namespace HBE::Serializers {

    BinaryReader::BinaryReader(std::vector<BinaryField> fields, std::filesystem::path source_path)
        : m_source_path(std::move(source_path)) {
        for (auto &f : fields)
            m_fields.emplace(f.key, std::move(f));
    }

    bool BinaryReader::Has(std::string_view key) const { return m_fields.count(key) > 0; }
    size_t BinaryReader::Size() const { return m_fields.size(); }

    void BinaryReader::Read(std::string_view key, bool &value) const {
        if (auto it = m_fields.find(key); it != m_fields.end())
            value = std::get<bool>(it->second.value);
    }
    void BinaryReader::Read(std::string_view key, int &value) const {
        if (auto it = m_fields.find(key); it != m_fields.end())
            value = std::get<int>(it->second.value);
    }
    void BinaryReader::Read(std::string_view key, float &value) const {
        if (auto it = m_fields.find(key); it != m_fields.end())
            value = std::get<float>(it->second.value);
    }
    void BinaryReader::Read(std::string_view key, std::string &value) const {
        if (auto it = m_fields.find(key); it != m_fields.end())
            value = std::get<std::string>(it->second.value);
    }
    void BinaryReader::Read(std::string_view key, uint8_t &value) const {
        if (auto it = m_fields.find(key); it != m_fields.end())
            value = std::get<uint8_t>(it->second.value);
    }
    void BinaryReader::Read(std::string_view key, uint32_t &value) const {
        if (auto it = m_fields.find(key); it != m_fields.end())
            value = std::get<uint32_t>(it->second.value);
    }
    void BinaryReader::Read(std::string_view key, int64_t &value) const {
        if (auto it = m_fields.find(key); it != m_fields.end())
            value = std::get<int64_t>(it->second.value);
    }
    void BinaryReader::Read(std::string_view key, glm::vec2 &value) const {
        if (auto it = m_fields.find(key); it != m_fields.end())
            value = std::get<glm::vec2>(it->second.value);
    }
    void BinaryReader::Read(std::string_view key, SDL_Color &value) const {
        if (auto it = m_fields.find(key); it != m_fields.end())
            value = std::get<SDL_Color>(it->second.value);
    }
    void BinaryReader::Read(std::string_view key, std::filesystem::path &value) const {
        if (auto it = m_fields.find(key); it != m_fields.end())
            value = std::get<std::filesystem::path>(it->second.value);
    }
    void BinaryReader::Read(std::string_view key, std::vector<std::string> &value) const {
        if (auto it = m_fields.find(key); it != m_fields.end())
            value = std::get<std::vector<std::string>>(it->second.value);
    }
    void BinaryReader::Read(std::string_view key, std::vector<std::filesystem::path> &value) const {
        if (auto it = m_fields.find(key); it != m_fields.end())
            value = std::get<std::vector<std::filesystem::path>>(it->second.value);
    }

} // namespace HBE::Serializers

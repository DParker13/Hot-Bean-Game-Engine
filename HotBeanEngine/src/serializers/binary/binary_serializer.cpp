#include <algorithm>
#include <fstream>
#include <stdexcept>

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/serializers/binary/binary_format_constants.hpp>
#include <HotBeanEngine/serializers/binary/binary_serialization_helpers.hpp>
#include <HotBeanEngine/serializers/binary/binary_serialization_reader.hpp>
#include <HotBeanEngine/serializers/binary/binary_serialization_writer.hpp>
#include <HotBeanEngine/serializers/binary/binary_serializer.hpp>

namespace HBE::Serializers {
    void BinarySerializer::Serialize(std::filesystem::path filepath, Core::ISerializable &object, bool append) {
        assert(!filepath.empty() && "Filepath is empty.");

        std::ofstream out(filepath, std::ios::binary);
        if (!out.is_open()) {
            LOG(Core::LoggingType::ERROR, "Failed to open binary file for write: " + filepath.string());
            return;
        }

        try {
            BinaryWriter writer;
            object.Serialize(writer);

            out.write(FormatBinary::MAGIC, sizeof(FormatBinary::MAGIC));
            WriteT<uint32_t>(out, FormatBinary::VERSION);
            WriteT<uint32_t>(out, static_cast<uint32_t>(writer.m_fields.size()));
            for (const auto &field : writer.m_fields) {
                WriteField(out, field);
            }
        } catch (const std::exception &e) {
            LOG(Core::LoggingType::ERROR,
                "Failed to serialize binary file: " + filepath.string() + " with error: " + e.what());
        } catch (...) {
            LOG(Core::LoggingType::ERROR, "Failed to serialize binary file: " + filepath.string());
        }

        if (!out.good()) {
            LOG(Core::LoggingType::ERROR, "Failed to write binary file: " + filepath.string());
        }
    }

    void BinarySerializer::Deserialize(std::filesystem::path filepath, Core::ISerializable &object) {
        assert(!filepath.empty() && "Filepath is empty.");

        std::ifstream in(filepath, std::ios::binary);
        if (!in.is_open()) {
            LOG(Core::LoggingType::ERROR, "Failed to open binary file for read: " + filepath.string());
            return;
        }

        try {
            char magic[4]{};
            in.read(magic, sizeof(magic));
            if (!in || !std::equal(std::begin(magic), std::end(magic), FormatBinary::MAGIC)) {
                LOG(Core::LoggingType::ERROR, "Invalid binary file: " + filepath.string());
                return;
            }

            const uint32_t version = ReadT<uint32_t>(in);
            if (!in || version != FormatBinary::VERSION) {
                LOG(Core::LoggingType::ERROR,
                    "Unsupported binary version " + std::to_string(version) + ": " + filepath.string());
                return;
            }

            const uint32_t field_count = ReadT<uint32_t>(in);
            std::vector<BinaryField> fields(field_count);
            for (auto &field : fields) {
                field = ReadField(in);
                if (!in) {
                    throw std::runtime_error("Unexpected end of binary file.");
                }
            }

            BinaryReader reader(std::move(fields), filepath);
            object.Deserialize(reader);
        } catch (const std::exception &e) {
            LOG(Core::LoggingType::ERROR,
                "Failed to deserialize binary file: " + filepath.string() + " with error: " + e.what());
        } catch (...) {
            LOG(Core::LoggingType::ERROR, "Failed to deserialize binary file: " + filepath.string());
        }
    }
} // namespace HBE::Serializers
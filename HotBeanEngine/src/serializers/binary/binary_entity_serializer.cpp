#include <fstream>
#include <stdexcept>

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/components/miscellaneous/transform_2d.hpp>
#include <HotBeanEngine/serializers/binary/binary_entity_serializer.hpp>
#include <HotBeanEngine/serializers/binary/binary_format_constants.hpp>
#include <HotBeanEngine/serializers/binary/binary_serialization_helpers.hpp>
#include <HotBeanEngine/serializers/binary/binary_serialization_reader.hpp>
#include <HotBeanEngine/serializers/binary/binary_serialization_writer.hpp>

namespace HBE::Serializers {
    using namespace Core;

    void BinaryEntitySerializer::Serialize(std::filesystem::path filepath, ISerializable &object, bool append) {
        assert(!filepath.empty() && "Filepath is empty.");

        std::ofstream out(filepath, std::ios::binary);
        if (!out.is_open()) {
            LOG(LoggingType::ERROR, "Failed to open binary scene for write: " + filepath.string());
            return;
        }

        try {
            out.write(FormatBinary::MAGIC, 4);
            WriteT<uint32_t>(out, FormatBinary::VERSION);

            BinaryWriter scene_writer;
            WriteT<uint32_t>(out, static_cast<uint32_t>(scene_writer.m_fields.size()));
            for (const auto &field : scene_writer.m_fields)
                WriteField(out, field);

            MapParentEntities();

            uint32_t root_count =
                m_parent_entity_map.count(-1) ? static_cast<uint32_t>(m_parent_entity_map[-1].size()) : 0;
            WriteT<uint32_t>(out, root_count);

            if (root_count > 0)
                WriteEntities(out, -1);
        } catch (const std::exception &e) {
            LOG(LoggingType::ERROR,
                "Failed to serialize binary scene: " + filepath.string() + " with error: " + e.what());
        } catch (...) {
            LOG(LoggingType::ERROR, "Failed to serialize binary scene: " + filepath.string());
        }

        if (!out.good()) {
            LOG(LoggingType::ERROR, "Failed to write binary scene: " + filepath.string());
        }
    }

    void BinaryEntitySerializer::WriteEntities(std::ostream &out, EntityID parent_entity) {
        for (EntityID entity : m_parent_entity_map[parent_entity])
            WriteEntity(out, entity);
    }

    void BinaryEntitySerializer::WriteEntity(std::ostream &out, EntityID entity) {
        auto components = g_ecs.GetAllComponents(entity);
        WriteT<uint32_t>(out, static_cast<uint32_t>(components.size()));

        for (auto *comp : components) {
            WriteStr(out, comp->GetName());
            BinaryWriter writer;
            comp->Serialize(writer);
            WriteT<uint32_t>(out, static_cast<uint32_t>(writer.m_fields.size()));
            for (const auto &f : writer.m_fields)
                WriteField(out, f);
        }

        uint32_t child_count =
            m_parent_entity_map.count(entity) ? static_cast<uint32_t>(m_parent_entity_map[entity].size()) : 0;
        WriteT<uint32_t>(out, child_count);
        if (child_count > 0)
            WriteEntities(out, entity);
    }

    void BinaryEntitySerializer::Deserialize(std::filesystem::path filepath, ISerializable &object) {
        assert(!filepath.empty() && "Filepath is empty.");

        std::ifstream in(filepath, std::ios::binary);
        if (!in.is_open()) {
            LOG(LoggingType::ERROR, "Failed to open binary scene for read: " + filepath.string());
            return;
        }

        try {
            m_deserialize_source_path = filepath;

            char magic[4];
            in.read(magic, 4);
            if (magic[0] != FormatBinary::MAGIC[0] || magic[1] != FormatBinary::MAGIC[1] ||
                magic[2] != FormatBinary::MAGIC[2] || magic[3] != FormatBinary::MAGIC[3]) {
                LOG(LoggingType::ERROR, "Invalid binary scene file (bad magic): " + filepath.string());
                return;
            }

            uint32_t version = ReadT<uint32_t>(in);
            if (version != FormatBinary::VERSION) {
                LOG(LoggingType::ERROR,
                    "Unsupported binary scene version " + std::to_string(version) + ": " + filepath.string());
                return;
            }

            uint32_t field_count = ReadT<uint32_t>(in);
            std::vector<BinaryField> fields(field_count);
            for (auto &field : fields)
                field = ReadField(in);

            BinaryReader reader(std::move(fields), m_deserialize_source_path);

            uint32_t root_count = ReadT<uint32_t>(in);
            ReadEntities(in, -1, root_count);
        } catch (const std::exception &e) {
            LOG(LoggingType::ERROR,
                "Failed to deserialize binary scene: " + filepath.string() + " with error: " + e.what());
        } catch (...) {
            LOG(LoggingType::ERROR, "Failed to deserialize binary scene: " + filepath.string());
        }
    }

    void BinaryEntitySerializer::ReadEntities(std::istream &in, EntityID parent_entity, uint32_t count) {
        for (uint32_t i = 0; i < count; ++i)
            ReadEntity(in, parent_entity);
    }

    void BinaryEntitySerializer::ReadEntity(std::istream &in, EntityID parent_entity) {
        EntityID entity = g_ecs.CreateEntity();

        uint32_t comp_count = ReadT<uint32_t>(in);
        for (uint32_t i = 0; i < comp_count; ++i) {
            std::string comp_name = ReadStr(in);
            uint32_t field_count = ReadT<uint32_t>(in);

            std::vector<BinaryField> fields(field_count);
            for (auto &f : fields)
                f = ReadField(in);

            if (g_ecs.IsComponentRegistered(comp_name)) {
                BinaryReader reader(std::move(fields), m_deserialize_source_path);
                g_app.GetComponentFactory()->CreateComponent(comp_name, reader, parent_entity, entity);
            }
            else {
                LOG(LoggingType::ERROR, "Unknown component in binary scene: " + comp_name);
            }
        }

        uint32_t child_count = ReadT<uint32_t>(in);
        ReadEntities(in, entity, child_count);
    }

    void BinaryEntitySerializer::MapParentEntities() {
        m_parent_entity_map.clear();
        for (EntityID entity = 0; entity < g_ecs.EntityCount(); entity++) {
            EntityID parent = -1;
            if (g_ecs.HasComponent<Components::Transform2D>(entity))
                parent = g_ecs.GetComponent<Components::Transform2D>(entity).m_parent;
            m_parent_entity_map[parent].push_back(entity);
        }
    }

} // namespace HBE::Serializers

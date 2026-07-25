#include <fstream>
#include <stdexcept>

#include <HotBeanEngine/application/application.hpp>
#include <HotBeanEngine/components/miscellaneous/transform_2d.hpp>
#include <HotBeanEngine/serializers/binary/binary_scene_serializer.hpp>
#include <HotBeanEngine/serializers/binary/binary_serialization_reader.hpp>
#include <HotBeanEngine/serializers/binary/binary_serialization_writer.hpp>

namespace HBE::Serializers {
    using namespace Core;

    // ---- Format constants ----
    static constexpr char kMagic[4] = {'H', 'B', 'S', 'C'};
    static constexpr uint32_t kVersion = 1;

    // ---- Write helpers ----
    template <typename T>
    static void WriteT(std::ostream &out, T val) {
        out.write(reinterpret_cast<const char *>(&val), sizeof(T));
    }

    static void WriteStr(std::ostream &out, std::string_view s) {
        WriteT<uint32_t>(out, static_cast<uint32_t>(s.size()));
        out.write(s.data(), static_cast<std::streamsize>(s.size()));
    }

    static void WriteField(std::ostream &out, const BinaryField &f) {
        WriteStr(out, f.key);
        WriteT<uint8_t>(out, static_cast<uint8_t>(f.type));
        std::visit(
            [&](auto &&val) {
                using T = std::decay_t<decltype(val)>;
                if constexpr (std::is_same_v<T, bool>)
                    WriteT<uint8_t>(out, val ? uint8_t{1} : uint8_t{0});
                else if constexpr (std::is_same_v<T, int>)
                    WriteT<int32_t>(out, static_cast<int32_t>(val));
                else if constexpr (std::is_same_v<T, float>)
                    WriteT<float>(out, val);
                else if constexpr (std::is_same_v<T, std::string>)
                    WriteStr(out, val);
                else if constexpr (std::is_same_v<T, uint8_t>)
                    WriteT<uint8_t>(out, val);
                else if constexpr (std::is_same_v<T, uint32_t>)
                    WriteT<uint32_t>(out, val);
                else if constexpr (std::is_same_v<T, int64_t>)
                    WriteT<int64_t>(out, val);
                else if constexpr (std::is_same_v<T, glm::vec2>) {
                    WriteT<float>(out, val.x);
                    WriteT<float>(out, val.y);
                }
                else if constexpr (std::is_same_v<T, SDL_Color>) {
                    WriteT<uint8_t>(out, val.r);
                    WriteT<uint8_t>(out, val.g);
                    WriteT<uint8_t>(out, val.b);
                    WriteT<uint8_t>(out, val.a);
                }
                else if constexpr (std::is_same_v<T, std::filesystem::path>)
                    WriteStr(out, val.string());
                else if constexpr (std::is_same_v<T, std::vector<std::string>>) {
                    WriteT<uint32_t>(out, static_cast<uint32_t>(val.size()));
                    for (const auto &s : val)
                        WriteStr(out, s);
                }
                else if constexpr (std::is_same_v<T, std::vector<std::filesystem::path>>) {
                    WriteT<uint32_t>(out, static_cast<uint32_t>(val.size()));
                    for (const auto &p : val)
                        WriteStr(out, p.string());
                }
            },
            f.value);
    }

    // ---- Read helpers ----
    template <typename T>
    static T ReadT(std::istream &in) {
        T val{};
        in.read(reinterpret_cast<char *>(&val), sizeof(T));
        return val;
    }

    static std::string ReadStr(std::istream &in) {
        uint32_t len = ReadT<uint32_t>(in);
        std::string s(len, '\0');
        in.read(s.data(), static_cast<std::streamsize>(len));
        return s;
    }

    static BinaryField ReadField(std::istream &in) {
        BinaryField f;
        f.key = ReadStr(in);
        f.type = static_cast<FieldType>(ReadT<uint8_t>(in));

        switch (f.type) {
        case FieldType::Bool:
            f.value = static_cast<bool>(ReadT<uint8_t>(in));
            break;
        case FieldType::Int:
            f.value = static_cast<int>(ReadT<int32_t>(in));
            break;
        case FieldType::Float:
            f.value = ReadT<float>(in);
            break;
        case FieldType::String:
            f.value = ReadStr(in);
            break;
        case FieldType::Uint8:
            f.value = ReadT<uint8_t>(in);
            break;
        case FieldType::Uint32:
            f.value = ReadT<uint32_t>(in);
            break;
        case FieldType::Int64:
            f.value = ReadT<int64_t>(in);
            break;
        case FieldType::Vec2: {
            float x = ReadT<float>(in);
            float y = ReadT<float>(in);
            f.value = glm::vec2{x, y};
            break;
        }
        case FieldType::Color: {
            SDL_Color c{};
            c.r = ReadT<uint8_t>(in);
            c.g = ReadT<uint8_t>(in);
            c.b = ReadT<uint8_t>(in);
            c.a = ReadT<uint8_t>(in);
            f.value = c;
            break;
        }
        case FieldType::Path:
            f.value = std::filesystem::path(ReadStr(in));
            break;
        case FieldType::VecString: {
            uint32_t n = ReadT<uint32_t>(in);
            std::vector<std::string> v(n);
            for (auto &s : v)
                s = ReadStr(in);
            f.value = std::move(v);
            break;
        }
        case FieldType::VecPath: {
            uint32_t n = ReadT<uint32_t>(in);
            std::vector<std::filesystem::path> v(n);
            for (auto &p : v)
                p = std::filesystem::path(ReadStr(in));
            f.value = std::move(v);
            break;
        }
        }
        return f;
    }

    // ---- BinarySceneSerializer ----

    void BinarySceneSerializer::MapParentEntities() {
        m_parent_entity_map.clear();
        for (EntityID entity = 0; entity < g_ecs.EntityCount(); entity++) {
            EntityID parent = -1;
            if (g_ecs.HasComponent<Components::Transform2D>(entity))
                parent = g_ecs.GetComponent<Components::Transform2D>(entity).m_parent;
            m_parent_entity_map[parent].push_back(entity);
        }
    }

    void BinarySceneSerializer::Serialize(std::filesystem::path filepath) {
        assert(!filepath.empty() && "Filepath is empty.");

        std::ofstream out(filepath, std::ios::binary);
        if (!out.is_open())
            throw std::runtime_error("Failed to open binary scene for write: " + filepath.string());

        out.write(kMagic, 4);
        WriteT<uint32_t>(out, kVersion);

        auto scene = g_app.GetSceneManager().GetCurrentScene();
        WriteStr(out, scene ? scene->m_name : "");

        MapParentEntities();

        uint32_t root_count = m_parent_entity_map.count(-1) ? static_cast<uint32_t>(m_parent_entity_map[-1].size()) : 0;
        WriteT<uint32_t>(out, root_count);

        if (root_count > 0)
            WriteEntities(out, -1);
    }

    void BinarySceneSerializer::WriteEntities(std::ostream &out, EntityID parent_entity) {
        for (EntityID entity : m_parent_entity_map[parent_entity])
            WriteEntity(out, entity);
    }

    void BinarySceneSerializer::WriteEntity(std::ostream &out, EntityID entity) {
        auto components = g_ecs.GetAllComponents(entity);
        WriteT<uint32_t>(out, static_cast<uint32_t>(components.size()));

        for (auto *comp : components) {
            WriteStr(out, comp->GetName());
            BinaryComponentWriter writer;
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

    void BinarySceneSerializer::Deserialize(std::filesystem::path filepath) {
        assert(!filepath.empty() && "Filepath is empty.");

        std::ifstream in(filepath, std::ios::binary);
        if (!in.is_open())
            throw std::runtime_error("Failed to open binary scene for read: " + filepath.string());

        char magic[4];
        in.read(magic, 4);
        if (magic[0] != kMagic[0] || magic[1] != kMagic[1] || magic[2] != kMagic[2] || magic[3] != kMagic[3])
            throw std::runtime_error("Invalid binary scene file: bad magic bytes.");

        uint32_t version = ReadT<uint32_t>(in);
        if (version != kVersion)
            throw std::runtime_error("Unsupported binary scene version: " + std::to_string(version));

        ReadStr(in); // scene name — already set on the IScene object

        uint32_t root_count = ReadT<uint32_t>(in);
        ReadEntities(in, -1, root_count);
    }

    void BinarySceneSerializer::ReadEntities(std::istream &in, EntityID parent_entity, uint32_t count) {
        for (uint32_t i = 0; i < count; ++i)
            ReadEntity(in, parent_entity);
    }

    void BinarySceneSerializer::ReadEntity(std::istream &in, EntityID parent_entity) {
        EntityID entity = g_ecs.CreateEntity();

        uint32_t comp_count = ReadT<uint32_t>(in);
        for (uint32_t i = 0; i < comp_count; ++i) {
            std::string comp_name = ReadStr(in);
            uint32_t field_count = ReadT<uint32_t>(in);

            std::vector<BinaryField> fields(field_count);
            for (auto &f : fields)
                f = ReadField(in);

            if (g_ecs.IsComponentRegistered(comp_name)) {
                BinaryComponentReader reader(std::move(fields));
                m_component_factory->CreateComponent(comp_name, reader, parent_entity, entity);
            }
            else {
                LOG(LoggingType::ERROR, "Unknown component in binary scene: " + comp_name);
            }
        }

        uint32_t child_count = ReadT<uint32_t>(in);
        ReadEntities(in, entity, child_count);
    }

} // namespace HBE::Serializers

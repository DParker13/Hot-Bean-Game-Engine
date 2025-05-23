#pragma once

#include <SDL.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <yaml-cpp/yaml.h>

namespace YAML {

    // Vec2
    template<>
    struct convert<glm::vec2> {
        static Node encode(const glm::vec2& v2) {
            Node node;

            node.push_back(v2.x);
            node.push_back(v2.y);

            return node;
        }
    
        static bool decode(const Node& node, glm::vec2& v2) {
            if(!node.IsSequence() || node.size() != 2) {
                return false;
            }
        
            v2.x = node[0].as<float>();
            v2.y = node[1].as<float>();

            return true;
        }
    };

    template<>
    struct convert<glm::ivec2> {
        static Node encode(const glm::ivec2& v2) {
            Node node;

            node.push_back(v2.x);
            node.push_back(v2.y);

            return node;
        }
    
        static bool decode(const Node& node, glm::ivec2& v2) {
            if(!node.IsSequence() || node.size() != 2) {
                return false;
            }
        
            v2.x = node[0].as<int>();
            v2.y = node[1].as<int>();

            return true;
        }
    };

    // Quaternion
    template<>
    struct convert<glm::quat> {
        static Node encode(const glm::quat& quat) {
            Node node;

            node.push_back(quat.x);
            node.push_back(quat.y);
            node.push_back(quat.z);
            node.push_back(quat.w);

            return node;
        }
    
        static bool decode(const Node& node, glm::quat& quat) {
            if(!node.IsSequence() || node.size() != 4) {
                return false;
            }
        
            quat.x = node[0].as<float>();
            quat.y = node[1].as<float>();
            quat.z = node[2].as<float>();
            quat.w = node[3].as<float>();

            return true;
        }
    };

    // Vec3
    template<>
    struct convert<glm::vec3> {
        static Node encode(const glm::vec3& v3) {
            Node node;

            node.push_back(v3.x);
            node.push_back(v3.y);
            node.push_back(v3.z);

            return node;
        }

        static bool decode(const Node& node, glm::vec3& v3) {
            if(!node.IsSequence() || node.size() != 3) {
                return false;
            }

            v3.x = node[0].as<float>();
            v3.y = node[1].as<float>();
            v3.z = node[2].as<float>();

            return true;
        }
    };

    // SDL_Color
    template<>
    struct convert<SDL_Color> {
        static Node encode(const SDL_Color& color) {
            Node node;

            node.push_back(color.r);
            node.push_back(color.g);
            node.push_back(color.b);
            node.push_back(color.a);

            return node;
        }

        static bool decode(const Node& node, SDL_Color& color) {
            if(!node.IsSequence() || node.size() != 4) {
                return false;
            }

            color.r = node[0].as<int>();
            color.g = node[1].as<int>();
            color.b = node[2].as<int>();
            color.a = node[3].as<int>();

            return true;
        }
    };
}

// Bitset
static std::bitset<16> string_to_bitset(const std::string& s) {
    assert(s.size() == 16 && "There must be 16 bits");

    std::bitset<16> bitset;
    for (int i = s.size() - 1; i >= 0; i--) {
        bitset.set(i, s[i] == '1');
    }

    return bitset;
}

// Vec2
inline YAML::Emitter& operator << (YAML::Emitter& out, const glm::vec2& v) {
    out << YAML::Flow;
    out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
    return out;
}

// iVec2
inline YAML::Emitter& operator << (YAML::Emitter& out, const glm::ivec2& v) {
    out << YAML::Flow;
    out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
    return out;
}

// Quat
inline YAML::Emitter& operator << (YAML::Emitter& out, const glm::quat& quat) {
    out << YAML::Flow;
    out << YAML::BeginSeq << quat.x << quat.y << quat.z << quat.w << YAML::EndSeq;
    return out;
}

// Vec3
inline YAML::Emitter& operator << (YAML::Emitter& out, const glm::vec3& vec) {
    out << YAML::Flow;
    out << YAML::BeginSeq << vec.x << vec.y << vec.z << YAML::EndSeq;
    return out;
}

// SDL_Color
inline YAML::Emitter& operator << (YAML::Emitter& out, const SDL_Color& color) {
    out << YAML::Flow;
    out << YAML::BeginSeq << (int)color.r << (int)color.g << (int)color.b << (int)color.a << YAML::EndSeq;
    return out;
}
#pragma once

#include <SDL3/SDL.h>
#include <glm/vec2.hpp>
#include <imgui.h>

namespace HBE::Application::GUI::PropertyNodes {
    class TexturePreview {
    public:
        static void RenderProperty(int &id, const char *label, SDL_Texture *texture) {
            ImGui::PushID(id++);
            ImGui::Text("%s", label);
            if (texture) {
                glm::vec2 size;
                SDL_GetTextureSize(texture, &size.x, &size.y);
                // Define the square size
                const float window_width = ImGui::GetWindowSize().x;

                // Calculate scaled dimensions to preserve aspect ratio
                float aspect_ratio = size.x / size.y;
                ImVec2 scaled_size;
                if (aspect_ratio > 1.0f) {
                    scaled_size = ImVec2(window_width, window_width / aspect_ratio);
                } else {
                    scaled_size = ImVec2(window_width * aspect_ratio, window_width);
                }

                ImGui::Image((void *)texture, scaled_size);
            } else {
                ImGui::Text("%s: No texture loaded.", label);
            }
            ImGui::PopID();
        }
    };
} // namespace HBE::Application::GUI::PropertyNodes
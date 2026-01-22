#include <HotBeanEngine/application/input_event_listener.hpp>

namespace HBE::Application {
    void InputEventListener::OnEvent(SDL_Event& event) {
        if (event.type == SDL_EVENT_KEY_DOWN && event.key.repeat == 0) {
            m_keys_pressed.insert(event.key.key);
            OnKeyDown(event);
        }
        else if (event.type == SDL_EVENT_KEY_UP) {
            m_keys_pressed.erase(event.key.key);
            OnKeyUp(event);
        }
        else if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            m_mouse_buttons_pressed.insert(event.button.button);
            OnMouseButtonDown(event);
        }
        else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
            m_mouse_buttons_pressed.erase(event.button.button);
            OnMouseButtonUp(event);
        }
        else if (event.type == SDL_EVENT_MOUSE_MOTION) {
            m_mouse_position = {event.motion.x, event.motion.y};
            OnMouseMove(event);
        }
    }
}
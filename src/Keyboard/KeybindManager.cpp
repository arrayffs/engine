#include "KeybindManager.h"

#include "../Window/Window.h"
#include "../Util/OrbitalCamera.h"

#include <glm/ext.hpp>

#include <map>
#include <print>

namespace keybind_manager {
  typedef int Key;
  std::map<Key, bool> g_keyboard;
  std::map<Key, bool> g_queued_releases;

  bool g_mouse[8];
  bool g_queued_mouse[8];
  glm::vec2 g_cached_cursor_pos = glm::vec2(0.f);

  glm::vec2 g_total_scroll = glm::vec2(0.f);

  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    switch (action)
    {
    case GLFW_PRESS:
      g_keyboard[key] = true;
      break;
    case GLFW_RELEASE:
      g_keyboard[key] = false;
    }
  }

  void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
  {
    g_cached_cursor_pos = { static_cast<float>(xpos), static_cast<float>(ypos) };
  }

  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
  {
    g_mouse[button] = action;
  }

  void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
  {
    g_total_scroll += glm::vec2(static_cast<float>(xoffset), static_cast<float>(yoffset));
  }

  bool key_down(int key)
  {
    return g_keyboard[key];
  }

  bool keypress(int key) {
    if (key_down(key)) {
      g_queued_releases[key] = true;
      return false;
    }

    bool state = g_queued_releases[key];
    g_queued_releases[key] = false;
    return state;
  }

  glm::vec2 cursor_pos()
  {
    return g_cached_cursor_pos;
  }

  bool lmb_down()
  {
    return g_mouse[GLFW_MOUSE_BUTTON_LEFT];
  }

  bool mmb_down()
  {
    return g_mouse[GLFW_MOUSE_BUTTON_MIDDLE];
  }

  bool rmb_down()
  {
    return g_mouse[GLFW_MOUSE_BUTTON_RIGHT];
  }

  void translate(glm::mat4& model)
  {
    static auto orbital_camera = OrbitalCamera::get_instance();

    { // mouse detach
      static bool cursor_locked = true;
      static bool init = false;
      if (!init) {
        init = true;
        window::set_cursor_lock(cursor_locked);
      }

      if (keybind_manager::keypress(GLFW_KEY_ESCAPE)) {
        cursor_locked = !cursor_locked;
        window::set_cursor_lock(cursor_locked);
      }
    }

    { // rots
      static bool pressed = false;
      static glm::vec2 last_point = glm::vec2(0.f);
      static glm::vec2 view_angles = glm::vec2(0.f);

      if (keybind_manager::rmb_down()) {
        if (!pressed) {
          last_point = keybind_manager::cursor_pos();
          pressed = true;
        }
        else {
          glm::vec2 current_point = keybind_manager::cursor_pos();
          glm::vec2 diff = (current_point - last_point) / -360.f;

          orbital_camera->rotate(diff);
          
          last_point = current_point;
        }
      }
      else if (pressed) pressed = false;
    }
    
    /*
    { // move - temporarily unavailable bcs i can't seem to fix a bug
      static bool pressed = false;
      static glm::vec2 last_point = glm::vec2(0.f);
      if (keybind_manager::mmb_down()) {
        if (!pressed) {
          last_point = keybind_manager::cursor_pos();
          pressed = true;
        }
        else {
          glm::vec2 current_point = keybind_manager::cursor_pos();
          glm::vec2 diff = current_point - last_point;
          orbital_camera->move({ 0.1f * diff.x, -0.1f * diff.y });

          last_point = current_point;
        }
      }
      else if (pressed) pressed = false;
    }
    */

    { // zoom
      static float last_scroll = 0.f;
      if (g_total_scroll.y != last_scroll) {
        float diff = g_total_scroll.y - last_scroll;
        last_scroll = g_total_scroll.y;

        //view = glm::translate(view, glm::vec3(0.f, 0.f, 0.5f * diff));
        orbital_camera->zoom(diff);

      }
    }
  }
}

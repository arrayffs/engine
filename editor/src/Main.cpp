#include <print>

#include <Engine.h>
#include <Keyboard/KeybindManager.h>
#include "Editor.h"
int main()
{
  Engine* engine = Engine::inst();
  engine->init();
  
  Window* window = engine->get_window_instance();

  window->set_key_callback(keybind_manager::key_callback);
  window->set_cursor_pos_callback(keybind_manager::cursor_position_callback);
  window->set_mouse_button_callback(keybind_manager::mouse_button_callback);
  window->set_scroll_callback(keybind_manager::scroll_callback);

  g_editor::camera.set_position(glm::vec3(-2.f, 2.f, 2.f));
  g_editor::camera.look_at(glm::vec3(0.f));

  bool wireframe{ false };
  do {
    keybind_manager::translate(engine->get_model());
    engine->set_view(g_editor::camera.get_view());

    if (keybind_manager::keypress(GLFW_KEY_W)) {
      
      if (!wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

      Logger::message("Engine", "Wireframe {}", wireframe ? "on" : "off");
      
      wireframe = !wireframe;
    }

  } while (engine->draw_frame());
  engine->shutdown();

  return 0;
}
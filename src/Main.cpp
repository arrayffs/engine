#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Keyboard/KeybindManager.h"
#include "Window/Window.h"
#include "Util/Defines.h"

#include "ObjectRenderer/ObjectLoader.h"
#include "Primitives/Texture.h"

int main(void)
{
  if (!window::create_window())
    return -1;

  ObjectRenderer cube = object_loader::load_from_file("res/Models/cube.obj", {-3.f, 0.f, 0.f});
  ObjectRenderer monke = object_loader::load_from_file("res/Models/monke.obj", {1.f, 0.f, 0.f});
  
  glm::mat4 model = glm::mat4(1.f);
  glm::mat4 view = glm::mat4(1.f);
  glm::mat4 proj = glm::mat4(1.f);

  view = glm::translate(view, glm::vec3(0.0f, -2.f, -5.f));

  bool lockedin = false;
  window::set_cursor_lock(lockedin);

  while (!window::should_close()) {
    window::newframe();
  
    {
      if (keybind_manager::key_down(GLFW_KEY_W))
        view = glm::translate(view, glm::vec3(0.0f, 0.f, 0.1f));
      if (keybind_manager::key_down(GLFW_KEY_S))
        view = glm::translate(view, glm::vec3(0.0f, 0.f, -0.1f));
      if (keybind_manager::key_down(GLFW_KEY_A))
        view = glm::translate(view, glm::vec3(0.1f, 0.f, 0.0f));
      if (keybind_manager::key_down(GLFW_KEY_D))
        view = glm::translate(view, glm::vec3(-0.1f, 0.f, 0.0f));


      if (keybind_manager::key_down(GLFW_KEY_R))
        view = glm::translate(view, glm::vec3(0.0f, -0.1f, 0.0f));
      if (keybind_manager::key_down(GLFW_KEY_F))
        view = glm::translate(view, glm::vec3(0.0f, 0.1f, 0.0f));

      if (keybind_manager::key_down(GLFW_KEY_Q))
        model = glm::rotate(model, glm::radians(1.f), glm::vec3(0.f, 1.f, 0.f));
      if (keybind_manager::key_down(GLFW_KEY_E))
        model = glm::rotate(model, glm::radians(-1.f), glm::vec3(0.f, 1.f, 0.f));

      if (keybind_manager::keypress(GLFW_KEY_J))
          monke.set_pos(monke.get_pos() + 1.f);
      if (keybind_manager::keypress(GLFW_KEY_U))
          monke.set_pos(monke.get_pos() - 1.f);

      if (keybind_manager::keypress(GLFW_KEY_ESCAPE)) {
        lockedin = !lockedin;
        window::set_cursor_lock(lockedin);
      }
    }
    
    proj = glm::perspective(glm::radians(90.f), (float)(window::properties::width / window::properties::height), 0.1f, 100.f);
    glViewport(0, 0, window::properties::width, window::properties::height);
    glScissor(0, 0, window::properties::width, window::properties::height);

    cube.render(model, view, proj);
    monke.render(model, view, proj);
 
    window::render();
    window::poll_events();
  }

  glfwTerminate();
  return 0;
}
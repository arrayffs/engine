#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <print>

#include "Keyboard/KeybindManager.h"
#include "Window/Window.h"
#include "Util/Defines.h"

#include "ObjectRenderer/ObjectLoader.h"
#include "Primitives/Texture.h"

int main(void)
{
  if (!window::create_window())
    return -1;

  ObjectRenderer cube = object_loader::load_from_file("res/Models/cube.obj", {-3.f, 0.f, 0.f}, "res/Shaders/3d.vert", "res/Shaders/texture_light.frag", "res/Textures/blue_ice.png");
  ObjectRenderer monke = object_loader::load_from_file("res/Models/monke.obj", {1.f, 0.f, 0.f}, "res/Shaders/3d.vert", "res/Shaders/texture_light.frag", "res/Textures/blue_ice.png");
  
  glm::mat4 model = glm::mat4(1.f);
  glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, -2.f, -5.f));
  glm::mat4 proj = glm::mat4(1.f);

  bool lockedin = false;
  window::set_cursor_lock(lockedin);

  while (!window::should_close()) {
    window::newframe();
  
    keybind_manager::translate(model, view, proj);
    
    // window resizing, i don't think this works in any way, shape or form.
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
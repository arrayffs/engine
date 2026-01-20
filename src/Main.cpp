#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <windows.h>
#include <stb_image.h>

#include "Keyboard/KeybindManager.h"
#include "Window/Window.h"
#include "Util/Defines.h"

#include "ObjectRenderer/ObjectLoader.h"

int main(void)
{
  if (!window::create_window())
    return -1;
  
  ObjectRenderer obj2(
    {
      glm::vec3(-0.5f,  -1.f, -0.5f), glm::vec3( 0.5f,  -1.f, -0.5f),
      glm::vec3(-0.5f,  -1.f,  0.5f), glm::vec3( 0.5f,  -1.f,  0.5f),
      glm::vec3(-0.5f,   1.f, -0.5f), glm::vec3( 0.5f,   1.f, -0.5f),
      glm::vec3(-0.5f,   1.f,  0.5f), glm::vec3( 0.5f,   1.f,  0.5f),
    },
    {
      /* bottom plane */
      0, 1, 2,
      1, 2, 3,
      /* top plane */
      4, 5, 6,
      5, 6, 7
    },
    "res/Shaders/monocolor_basic.vert", "res/Shaders/monocolor_basic.frag"
  );
  float obj2_colors[4] = { 1.f, 0.0f, 0.0f, 0.5f };
  obj2.set_uniform_4f("u_Color", obj2_colors);

  //auto obj2 = object_loader::load_object("res/Models/cube.obj");

  int width, height, num_color_ch;
  unsigned char* bytes = stbi_load("res/Textures/pop_cat.png", &width, &height, &num_color_ch, 0);

  unsigned int texture;
  glGenTextures(1, &texture);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE0, texture);
  glTexParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexParameteri(texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

  float flat_color[] = { 1.0f, 1.0f, 1.f, 1.f };
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flat_color);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
  glGenerateMipmap(texture);

  stbi_image_free(bytes);
  glBindTexture(GL_TEXTURE_2D, 0);

  glm::mat4 model = glm::mat4(1.f);
  glm::mat4 view = glm::mat4(1.f);
  glm::mat4 proj = glm::mat4(1.f);

  view = glm::translate(view, glm::vec3(0.0f, -2.f, -5.f));

  bool lockedin = true;
  window::set_cursor_lock(true);

  while (!window::should_close()) {
    window::newframe();
  
    obj2.bind();

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

    if (keybind_manager::keypress(GLFW_KEY_ESCAPE)) {
      lockedin = !lockedin;
      window::set_cursor_lock(lockedin);
    }

    proj = glm::perspective(glm::radians(90.f), (float)(window::properties::width / window::properties::height), 0.1f, 100.f);
    
    obj2.set_uniform_mat4("model", model);
    obj2.set_uniform_mat4("view", view);
    obj2.set_uniform_mat4("proj", proj);

    obj2.render(false);
   
    window::render();
    window::poll_events();
  }

  glfwTerminate();
  return 0;
}
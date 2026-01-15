#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

namespace keybind_manager {
  bool key_down(int key);
  bool keypress(int key);

  glm::vec2 cursor_pos();
  bool lmb_down();
  bool mmb_down();
  bool rmb_down();
  
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
  void mouse_key_callback(GLFWwindow* window, int key, int action, int mods);
}
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace keybind_manager {
  bool key_down(int key);
  bool keypress(int key);

  glm::vec2 cursor_pos();
  bool lmb_down();
  bool mmb_down();
  bool rmb_down();
  
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
  void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
  void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

  void translate(glm::mat4& model, glm::mat4& view, glm::mat4& proj);
}
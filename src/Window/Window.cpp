#include "Window.h"
#include "../Keyboard/KeybindManager.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <print>
#include <string>

GLFWwindow* _window;

bool window::create_window()
{
  if (!glfwInit())
    return false;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  _window = glfwCreateWindow(properties::width, properties::height, "autistic engine", NULL, NULL);
  if (!_window) {
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(_window);
  glfwSwapInterval(1);
  if (glewInit() != GLEW_OK) {
    glfwTerminate();
    return false;
  }

  glEnable(GL_DEPTH_TEST);
  glfwSetKeyCallback(_window, keybind_manager::key_callback);
  glfwSetCursorPosCallback(_window, keybind_manager::cursor_position_callback);
  glfwSetMouseButtonCallback(_window, keybind_manager::mouse_button_callback);
  glfwSetScrollCallback(_window, keybind_manager::scroll_callback);

  return true;
}

bool window::should_close()
{
  return glfwWindowShouldClose(_window);
}

void window::newframe()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void window::render()
{
  glfwSwapBuffers(_window);
}

void window::poll_events()
{
  while (GLenum err = glGetError())
    std::println("[OpenGL] Error 0x{:X}", err);

  glfwPollEvents();
}

void window::set_cursor_lock(bool state)
{
  if (state)
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  else 
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
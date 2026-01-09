#include "Window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLFWwindow* _window;

bool window::create_window()
{
  if (!glfwInit())
    return false;

  _window = glfwCreateWindow(800, 800, "circle", NULL, NULL);
  if (!_window) {
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(_window);
  //glfwSwapInterval(0); // vsync
  if (glewInit() != GLEW_OK) {
    glfwTerminate();
    return false;
  }

  return true;
}

bool window::should_close()
{
  return glfwWindowShouldClose(_window);
}

void window::newframe()
{
  glClear(GL_COLOR_BUFFER_BIT);
}

void window::render()
{
  glfwSwapBuffers(_window);
}

void window::poll_events()
{
  glfwPollEvents();
}

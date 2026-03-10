#include "Window.h"
#include "../Keyboard/KeybindManager.h"

#include "../Util/GLConfig.h"

#include <print>
#include <string>

GLFWwindow* _window;

bool window::create_window()
{
  if (!glfwInit()) {
    std::println("GLFW Could not initialize");
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  _window = glfwCreateWindow(properties::width, properties::height, "autistic engine", NULL, NULL);
  if (!_window) {
    std::println("glfwCreateWindow() failed.");
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(_window);
  glfwSwapInterval(0);
#ifdef __unix__
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::println("Failed to initialize GLAD");
    return false;
  }
#else
  if (glewInit() != GLEW_OK) {
    std::println("GLEW Error: {}", (const char*)glewGetErrorString(err));
    glfwTerminate();
    return false;
  }
#endif

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

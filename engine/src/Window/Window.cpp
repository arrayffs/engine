#include <Window/Window.h>

#include <print>
#include <string>
#include <Utility/Logger.h>

Window::Window()
{
  if (!glfwInit()) {
    return;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, 16);

  _handle = glfwCreateWindow(_width, _height, "Hypoxia", NULL, NULL);
  if (!_handle) {
    Logger::error("Window", "glfwCreateWindow() failed.");
    glfwTerminate();
    return;
  }

  glfwMakeContextCurrent(_handle);
  glfwSwapInterval(1);
#ifdef __unix__
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    Logger::error("Window", "Failed to initialize GLAD.");
    _handle = nullptr;
    return;
  }
#else
  auto err = glewInit();
  if (err != GLEW_OK) {
    Logger::error("Window", "GLEW Error: {}", (const char*)glewGetErrorString(err));
    glfwTerminate();
    _handle = nullptr;
    return;
  }

#endif

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_MULTISAMPLE);
  //glEnable(GL_FRAMEBUFFER_SRGB);

  //glfwSetKeyCallback(_handle, keybind_manager::key_callback);
  //glfwSetCursorPosCallback(_handle, keybind_manager::cursor_position_callback);
  //glfwSetMouseButtonCallback(_handle, keybind_manager::mouse_button_callback);
  //glfwSetScrollCallback(_handle, keybind_manager::scroll_callback);

  Logger::message("Window", "Created successfully");
  return;
}

bool Window::should_close()
{
  return glfwWindowShouldClose(_handle);
}

void Window::new_frame()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::render()
{
  glfwSwapBuffers(_handle);
}

void Window::poll_events()
{
  while (GLenum err = glGetError())
    std::println("[OpenGL] Error 0x{:X}", err);

  glfwPollEvents();
}

void Window::set_cursor_lock(bool state)
{
  if (state)
    glfwSetInputMode(_handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  else
    glfwSetInputMode(_handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

glm::vec2 Window::calc_ndc()
{
  double x{}, y{};
  glfwGetCursorPos(_handle, &x, &y);

  return glm::vec2(
    2 * x / _width - 1,
    1 - 2 * y / _height
  );
}
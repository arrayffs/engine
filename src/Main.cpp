#include <stdexcept>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window/Window.h"
#include "Shader/Shader.h"
#include "Util/Math.h"

int main(void)
{
  if (!window::create_window())
    return -1;

  Vector2 positions[] = {
    { -0.5,  0.5 }, { 0.5,  0.5 },
    { -0.5, -0.5 }, { 0.5, -0.5 }
  };

  unsigned int indices[] = {
    0, 1, 2,
    1, 2, 3
  };

  unsigned int buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);

  unsigned int ibo;
  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

  std::string triag_frag = shaders::load_shader("res/Shaders/triag.frag");
  std::string triag_vert = shaders::load_shader("res/Shaders/triag.vert");
  unsigned int shader = shaders::create_shader(triag_vert, triag_frag);
  glUseProgram(shader);

  while (!window::should_close()) {
    window::newframe();
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    window::render();
    window::poll_events();
  }

  glfwTerminate();
  return 0;
}
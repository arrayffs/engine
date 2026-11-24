#include "Engine.h"

#include <Utility/Logger.h>
#include <Lighting/Program.h>


bool Engine::init()
{
  
  Logger::message("Engine", "Initialized");
  return true;
}

bool Engine::shutdown()
{
  Logger::message("Engine", "Shutting down gracefully...");

  return true;
}

bool Engine::draw_frame()
{
  _window.new_frame();

  _proj = glm::perspective(
    glm::radians(45.f),
    (float)_window.width() / (float)_window.height(),
    0.1f, 100.f
  );

  static Program program = Program("res/Shaders/3d.vs", "res/Shaders/3d.fs");
  program.bind();

  int u_model = glGetUniformLocation(program.get_id(), "u_model");
  glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(_model));
  
  int u_proj = glGetUniformLocation(program.get_id(), "u_proj");
  glUniformMatrix4fv(u_proj, 1, GL_FALSE, glm::value_ptr(_proj));
  
  int u_view = glGetUniformLocation(program.get_id(), "u_view");
  glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(_view));

  /*
  * 0   1
  *   4
  * 3   2
  */
  static Mesh mesh = Mesh(
    {
      { { 0.f, 0.f, 0.f } },
      { { 1.f, 0.f, 0.f } },
      { { 1.f, 0.f, 1.f } },
      { { 0.f, 0.f, 1.f } },
      { { 0.5f, 1.f, 0.5f } },
    },
    {
      0, 1, 4,
      1, 2, 4,
      2, 3, 4,
      3, 0, 2,
      0, 1, 3,
      1, 3, 2
    }
  );

  mesh.render(_model, _view, _proj);

  _window.render();
  _window.poll_events();
  return !_window.should_close();
}

#pragma warning (disable: 4100 4267)

#include <Engine.h>

#include <Utility/Logger.h>
#include <Lighting/Program.h>
#include <Lighting/Raycast/Raycast.h>

bool Engine::init()
{
  Logger::message("Engine", "Initialized");

  auto cube = _asset_manager->load_asset("res/Models/cube.obj");
  if (cube.has_value()) {
    for (float x = -5; x < 5; ++x) {
      for (float z = -5; z < 5; ++z) {
        _world.add_object(cube.value(), glm::vec3(5.f * x, 0.f, 5.f * z));
      }
    }
  }

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

  int u_position = glGetUniformLocation(program.get_id(), "u_position");
  int u_hovered = glGetUniformLocation(program.get_id(), "u_hovered");

  static Raycast* raycast = Raycast::inst();
  BaseObject* hovered_object = raycast->get_hovered_object(_window.calc_ndc());

  for (BaseObject* obj : _world._objects) {
    glUniform1i(u_hovered, hovered_object == obj ? 1 : 0);
    obj->render(u_position);
  }

  _window.render();
  _window.poll_events();
  return !_window.should_close();
}

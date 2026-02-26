#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Singleton.h"

class OrbitalCamera: public singleton<OrbitalCamera>
{
private:
  glm::vec3 _position{ 0.f };
  glm::vec3 _pivot_point { 0.f };
  glm::vec3 _up{ 0.f };
  glm::vec3 _direction{ 0.f };

  glm::mat4 _view;

public:
  OrbitalCamera() = default;
  //OrbitalCamera(glm::vec3 position, glm::vec3 pivot_point);

  void set_position(glm::vec3 position);
  void set_pivot_point(glm::vec3 position);
  void move(glm::vec3 relative_position);

  render_data_t recalculate();

  void update();

  glm::mat4 get_view() const { return _view; }
};


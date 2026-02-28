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

  void set_position(glm::vec3 position);
  void set_pivot_point(glm::vec3 position);
  void move(glm::vec2 relative_position);
  void zoom(float relative_zoom);
  void set_zoom(float zoom);

  void rotate(glm::vec2 angle);

  void update();

  glm::mat4 get_view() const { return _view; }
  glm::vec3 pivot_position() const { return _pivot_point; }
};


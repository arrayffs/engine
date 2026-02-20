#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class OrbitalCamera
{
private:
  glm::vec2 _angle { 0.f };
  glm::vec3 _pivot_point { 0.f };
public:
  OrbitalCamera(glm::vec3 position, float distance);

  void set_angle(glm::vec2 angle);
  void rotate(glm::vec2 relative_angle);

  void set_pos(glm::vec3 position);
  void move(glm::vec3 relative_position);

  glm::mat4 get_model();
  glm::mat4 get_view();
};


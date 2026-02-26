#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class OrbitalCamera
{
public:
  struct render_data_t {
    glm::mat4 _model;
    glm::mat4 _proj;
  };

private:
  glm::vec3 _position{ 0.f };
  glm::vec3 _pivot_point { 0.f };

public:
  OrbitalCamera(glm::vec3 position, glm::vec3 pivot_point);

  render_data_t recalculate();

  render_data_t set_rotation(glm::vec2 angle);
  render_data_t rotate(glm::vec2 relative_angle);

  render_data_t get_data();
};


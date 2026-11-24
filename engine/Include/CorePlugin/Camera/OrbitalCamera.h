#pragma once

#include "Camera.h"

class OrbitalCamera final
  : public Camera
{
public:
  OrbitalCamera(glm::vec3 position, glm::vec3 target);
  OrbitalCamera(glm::vec3 position, glm::vec2 angle);

  void look_at(glm::vec3 coordinate) override;
  void rotate(glm::vec2 angle) override;
  glm::mat4 get_view() const override;
  
  void zoom(float relative_zoom) override;
  void set_zoom(float zoom) override;

};
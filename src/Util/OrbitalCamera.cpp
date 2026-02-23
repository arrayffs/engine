#include "OrbitalCamera.h"

OrbitalCamera::OrbitalCamera(glm::vec3 position, glm::vec3 pivot_point)
  : _position(position), _pivot_point(pivot_point)
{
  update();
}
#include "OrbitalCamera.h"

void OrbitalCamera::set_position(glm::vec3 position)
{
  _position = position;
  update();
}

void OrbitalCamera::set_pivot_point(glm::vec3 position)
{
  _pivot_point = position;
  update();
}

void OrbitalCamera::move(glm::vec3 relative_position)
{
  _pivot_point += relative_position;
  update();
}

void OrbitalCamera::rotate(glm::vec2 angle)
{
  glm::vec3 dir;

  dir.x = glm::cos(angle.y) * sin(angle.x);
  dir.y = glm::sin(angle.y);
  dir.z = glm::cos(angle.y) * cos(angle.x);

  _position += normalize(dir);

  update();
}

void OrbitalCamera::update()
{
  _view = glm::lookAt(
    _position,
    _pivot_point,
    glm::vec3(0.f, 1.f, 0.f)
  );
}
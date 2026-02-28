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
  _position += relative_position;
  _pivot_point += relative_position;
  
  update();
}

void OrbitalCamera::zoom(float relative_zoom)
{
  glm::vec3 dir = _position - _pivot_point;
  float radius = glm::length(dir);
  if (radius == 0.0f)
    return;

  glm::vec3 normalized = dir / radius;
  float new_zoom = -relative_zoom + radius;

  _position = _pivot_point + normalized * new_zoom;
  update();
}

void OrbitalCamera::set_zoom(float zoom)
{
  glm::vec3 dir = _position - _pivot_point;
  float radius = glm::length(dir);
  if (radius == 0.0f)
    return;

  glm::vec3 normalized = dir / radius;


  _position = _pivot_point + normalized * -zoom;
  update();
}

void OrbitalCamera::rotate(glm::vec2 angle)
{
  glm::vec3 dir = _position - _pivot_point;

  glm::mat4 rot(1.0f);
  rot = glm::rotate(rot, angle.x, glm::vec3(0.0f, 1.0f, 0.0f));
  rot = glm::rotate(rot, angle.y, glm::vec3(1.0f, 0.0f, 0.0f));

  glm::vec3 rotated = glm::vec3(rot * glm::vec4(dir, 1.0f));
  _position = _pivot_point + rotated;

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
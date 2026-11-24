#include <CorePlugin/Camera/OrbitalCamera.h>
#include <cmath>

namespace
{
  const glm::vec3 g_world_up      { 0.f, 1.f, 0.f };
  constexpr float g_max_pitch_dot { 0.99f };
}

OrbitalCamera::OrbitalCamera(glm::vec3 position, glm::vec3 target)
  : Camera(position, target)
{
}

OrbitalCamera::OrbitalCamera(glm::vec3 position, glm::vec2 angle)
  : Camera(position, glm::vec3(0.f))
{
  rotate(angle);
}

void OrbitalCamera::look_at(glm::vec3 target)
{
  _target = target;
}

void OrbitalCamera::rotate(glm::vec2 angle)
{
  glm::vec3 offset = _position - _target;
  offset = glm::mat3(glm::rotate(glm::mat4(1.f), angle.x, g_world_up)) * offset;

  glm::vec3 right = glm::normalize(glm::cross(g_world_up, offset));
  glm::vec3 pitched = glm::mat3(glm::rotate(glm::mat4(1.f), angle.y, right)) * offset;

  if (std::abs(glm::normalize(pitched).y) < g_max_pitch_dot)
    offset = pitched;

  _position = _target + offset;
}

glm::mat4 OrbitalCamera::get_view() const
{
  return glm::lookAt(_position, _target, g_world_up);
}

void OrbitalCamera::zoom(float relative_zoom)
{
  glm::vec3 dir = _position - _target;
  float radius = glm::length(dir);
  if (radius == 0.0f)
    return;

  glm::vec3 normalized = dir / radius;
  float new_zoom = -relative_zoom + radius;

  _position = _target + normalized * new_zoom;
}

void OrbitalCamera::set_zoom(float zoom)
{
  glm::vec3 dir = _position - _target;
  float radius = glm::length(dir);
  if (radius == 0.0f)
    return;

  glm::vec3 normalized = dir / radius;


  _position = _target + normalized * -zoom;
}

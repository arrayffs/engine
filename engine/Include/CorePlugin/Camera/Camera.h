#pragma once

#include <Engine.h>

class Camera
{
protected:
  glm::vec3 _position{ };
  glm::vec3 _target{ };

  Camera(glm::vec3 position, glm::vec3 target);
public:
  virtual ~Camera() = default;

  virtual void look_at(glm::vec3 coordinate) = 0;
  virtual void rotate(glm::vec2 angle) = 0;
  virtual glm::mat4 get_view() const = 0;

  virtual void zoom(float relative_zoom) = 0;
  virtual void set_zoom(float zoom) = 0;

  void set_position(glm::vec3 position) { _position = position; }

  glm::vec3 get_position() const { return _position; }
  glm::vec3 get_target() const { return _target; }
  
};
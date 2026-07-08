#ifndef _RAYTRACER_H_
#define _RAYTRACER_H_

#include "../Util/Singleton.h"

#include <optional>

#include <glm/glm.hpp>
#include <glm/ext.hpp>


class Raytracer : public singleton<Raytracer>
{
protected:
  std::optional<glm::vec3> ray_intersects_triangle(const glm::vec3& ray_origin, const glm::vec3& ray_vector, const glm::vec3& a, const glm::vec3& b, const glm::vec3 c);
public:
  std::optional<glm::vec3> raycast(glm::vec3& origin, glm::vec3& direction, float max_distance = 1000.f);
};

#endif // !_RAYTRACER_H_
#include "Raytracer.h"
#include "CollisionRegistry.h"

#include <print>

std::optional<glm::vec3> Raytracer::ray_intersects_triangle(const glm::vec3& ray_origin, const glm::vec3& ray_vector, const glm::vec3& a, const glm::vec3& b, const glm::vec3 c)
{
  constexpr float epsilon = std::numeric_limits<float>::epsilon();

  glm::vec3 edge1 = b - a;
  glm::vec3 edge2 = c - a;

  const glm::vec3 normal = glm::cross(edge1, edge2);
  if (glm::dot(normal, ray_vector) > 0) return {};

  glm::vec3 ray_cross_e2 = cross(ray_vector, edge2);
  float det = glm::dot(edge1, ray_cross_e2);

  if (abs(det) < epsilon) return {}; // ray is parallel to triangle

  float inv_det = 1.0 / det;
  glm::vec3 s = ray_origin - a;
  float u = inv_det * glm::dot(s, ray_cross_e2);

  if (u < -epsilon || u - 1 > epsilon) return {}; // ray passes outside edge2 bounds

  glm::vec3 s_cross_e1 = glm::cross(s, edge1);
  float v = inv_det * glm::dot(ray_vector, s_cross_e1);

  if (v < -epsilon || u + v - 1 > epsilon) return {}; // ray passes outside edge1 bounds

  float t = inv_det * glm::dot(edge2, s_cross_e1);
  if (t > epsilon) {
    return  glm::vec3(ray_origin + ray_vector * t);
  }
  else return {}; // there is a line intersection but not a ray intersection.
}

std::optional<glm::vec3> Raytracer::raycast(glm::vec3& origin, glm::vec3& direction, float max_distance)
{
  static auto* registry = CollisionRegistry::get_instance();
  std::lock_guard<std::mutex> lock(registry->_mesh_lock);

  float nearest_distance = std::numeric_limits<float>::max();
  Mesh* nearest_mesh{ nullptr };
  glm::vec3 impact = glm::vec3(0.f);

  std::vector<Mesh*> hovered_meshes{};
  for (auto& mesh : registry->_meshes) {
    auto& indices = mesh->get_vertex_array().get_indices_cache();
    auto& vertexes = mesh->get_buffer_array().get_vertex_positions();

    for (int i = 0; i < indices.size(); i += 3) {
      glm::vec3 a = vertexes[indices[i]]    ._world_pos;
      glm::vec3 b = vertexes[indices[i + 1]]._world_pos;
      glm::vec3 c = vertexes[indices[i + 2]]._world_pos;

      auto ray_result = ray_intersects_triangle(origin, direction, a, b, c);
      if (ray_result.has_value()) {
        auto distance = glm::distance(origin, ray_result.value());

        if (distance < nearest_distance) {
          nearest_distance = distance;
          impact = ray_result.value();
          nearest_mesh = mesh;
          break;
        }
      }
      else if (mesh->is_hovered())
        hovered_meshes.push_back(mesh);
    }
  }

  if (!nearest_mesh)
    return std::nullopt;

  for (auto* m : hovered_meshes) {
    m->set_hovered(false);
  }

  nearest_mesh->set_hovered(true);

  return impact;
}

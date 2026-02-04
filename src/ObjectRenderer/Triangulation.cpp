#include "Triangulation.h"
#include "../Util/Defines.h"

#include <glm/glm.hpp>
#include <cmath>
#include <print>
namespace triangulation {
  std::vector<unsigned int> triangulation::delaunay(const std::vector<vertex_t>& face)
  {
    glm::vec3 min = glm::vec3(0x7FFFFFF);
    glm::vec3 max = glm::vec3(0);

    float side_size = 1.0f;

    for (const auto& f : face) {
      min = {
        std::min(f._world_pos.x, min.x),
        std::min(f._world_pos.y, min.y),
        std::min(f._world_pos.z, min.z)
      };

      max = {
        std::max(f._world_pos.x, max.x),
        std::max(f._world_pos.y, max.y),
        std::max(f._world_pos.z, max.z)
      };
    }

    /*
    * Supertriangle
    */
    float a = (max.x - min.x) / 2.f;
    float b = (max.y - min.y) / 2.f;
    float angle1 = std::atanf(a/b);
    float angle2 = 90 - angle1;
    float c = angle1 / std::sinf(angle2);

    glm::vec2 C = {
      min.x + a,
      min.y + b + std::sqrtf(c - a)
    };

    glm::vec2 A = {
      min.x, min.y
    };

    glm::vec2 B = {
      max.x, min.y
    };

    
    b = std::sqrtf(std::powf(b + std::sqrtf(c - a), 2) + std::powf(a * 2, 2));
    c = b;
    a *= 4;

    /*
    * 
    */

    return {};
  }
}
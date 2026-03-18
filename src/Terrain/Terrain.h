#pragma once

#include "../Util/Defines.h"
#include <mutex>

namespace generator_config {
  float min_ceil{ -5.f };
  float max_ceil{ 5.f };

  float point_density{ 16.f };
}

class Terrain
{
private:
  std::vector<vertex_t> _terrain;
public:
  std::vector<vertex_t> get() const { return _terrain; }

  void generate(unsigned int seed, glm::vec2 grid_size = {256.f, 256.f});

  std::vector<vertex_t>& get_mut() { return _terrain; }
};
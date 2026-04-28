#pragma once

#include "../ObjectRenderer/ObjectRenderer.h"
#include "../Util/Defines.h"
#include <mutex>

namespace generator_config {
  float min_ceil{ -5.f };
  float max_ceil{ 5.f };

  float point_density{ 16.f };
}

class Terrain: public ObjectRenderer
{
public:
  Terrain();

  void generate(unsigned int seed, glm::vec2 grid_size = {256.f, 256.f});
};
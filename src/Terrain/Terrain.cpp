#include "Terrain.h"

void Terrain::generate(unsigned int seed, glm::vec2 grid_size)
{
  srand(seed);


  for (float x = grid_size.x * -0.5f; x < grid_size.x * 0.5f; x += generator_config::point_density) {
    for (float y = grid_size.x * -0.5f; y < grid_size.x * 0.5f; y += generator_config::point_density) {

      glm::vec3 point = { x, rand() % ( generator_config::max_ceil- generator_config::min_ceil + 1) + generator_config::min_ceil, y };



    }
  }
}

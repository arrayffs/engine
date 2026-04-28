#include "Terrain.h"

#include <stack>

Terrain::Terrain()
  : ObjectRenderer(
    ObjectType::MODEL,
    "res/Shaders/3d.vert",
    "res/Shaders/texture_light.frag",
    { "res/Textures/pop_cat.png" }
  )
{
  
}

void Terrain::generate(unsigned int seed, glm::vec2 grid_size)
{
  srand(seed);

  std::vector<vertex_t> vertexes;
  std::vector<unsigned int> indices;

  int i{ 0 }, y{ 0 };
  while (i < 256 || y < 256) {
    if (i < 255) ++i;


    //if (y < 255) ++y;



  }


  upload(vertexes, indices);
}

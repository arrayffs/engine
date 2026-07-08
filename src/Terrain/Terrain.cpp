#include "Terrain.h"
#include <random>
#include <stack>

Terrain::Terrain()
{
  
}

void Terrain::generate(unsigned int seed, glm::vec2 grid_size)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(0, 100);

  std::vector<vertex_t> vertexes;
  std::vector<unsigned int> indices;

  
  for (int x = 0; x < grid_size.x; ++x) {
    for (int y = 0; y < grid_size.y; ++y) {

      //      +      !+      !+
      // !+ [0, 0]+[1, 0] [2, 0]
      //      +      +      +
      // !+ [0, 1]+[1, 1] [2, 1]
      // !+ [0, 2]+[1, 2] [2, 2]

      auto up = x * (y - 1);
      auto left = (x - 1) * y;

      int h = 0;
      if (up > 0 && up < vertexes.size() &&
          left > 0 && left < vertexes.size()) {
        auto up_y = vertexes[up]._world_pos.y;
        auto left_y = vertexes[left]._world_pos.y;

        auto avg = (up_y + left_y) * 0.5f;
        h = avg + static_cast<float>(distr(gen)) * 0.1f;
      }

      vertexes.push_back({ { x - grid_size.x * 0.5f, /*h*/ 0.f, y - grid_size.y * 0.5f}});

      if (x + 1 < grid_size.x && y + 1 < grid_size.y) {
        int tl = x * grid_size.y + y;
        int tr = x * grid_size.y + (y + 1);
        int bl = (x + 1) * grid_size.y + y;
        int br = (x + 1) * grid_size.y + (y + 1);

        indices.push_back(tl);
        indices.push_back(tr);
        indices.push_back(bl);

        indices.push_back(tr);
        indices.push_back(br);
        indices.push_back(bl);
      }
    }
  }

  for (size_t i = 0; i < indices.size(); i += 3)
  {
    auto& a = vertexes[indices[i]];
    auto& b = vertexes[indices[i + 1]];
    auto& c = vertexes[indices[i + 2]];

    glm::vec3 e1 = b._world_pos - a._world_pos;
    glm::vec3 e2 = c._world_pos - a._world_pos;

    glm::vec3 n = glm::normalize(glm::cross(e1, e2));

    a._normal += n;
    b._normal += n;
    c._normal += n;
  }

  for (auto& v : vertexes)
    v._normal = glm::normalize(v._normal);

  _program = Program("res/Shaders/3d.vert", "res/Shaders/texture_light.frag");
  _mesh = {
    ObjectType::MODEL,
    vertexes, indices, _program, _material
  };
}

void Terrain::render(glm::mat4& model, glm::mat4& view, glm::mat4& proj, glm::vec3& light_source, glm::vec3& position)
{
  _mesh.render(model, view, proj, light_source, position);
}

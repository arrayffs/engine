#ifndef _MESH_H_
#define _MESH_H_

#include <glm/glm.hpp>
#include <vector>
#include <utility>

struct vertex_t
{
  glm::vec3 _world  { };
  glm::vec3 _normal { };
  glm::vec2 _tex    { };
};

class Mesh
{
public:
  std::vector<vertex_t> _vertex{ };
  std::vector<uint32_t> _indices{ };

  std::pair<glm::vec3, glm::vec3> _bounding_box{ };

protected:

  // vertex array object - basically config of the mesh
  uint32_t _vao{ };
  // vertex buffer object - holds raw vertex_t data
  uint32_t _vbo{ };
  // index buffer object - holds indice data
  uint32_t _ebo{ };
public:
  Mesh(std::vector<vertex_t> vertex, std::vector<uint32_t> indices);

  void bind();
  void render();
};

#endif // !_MESH_H_
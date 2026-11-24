#ifndef _MESH_H_
#define _MESH_H_

#include <glm/glm.hpp>
#include <vector>

struct vertex_t
{
  glm::vec3 _world  { };
  glm::vec3 _normal { };
  glm::vec2 _tex    { };
};

class Mesh
{
protected:
  std::vector<vertex_t> _vertex { };
  std::vector<uint32_t> _indices { };

  // vertex array object - basically config of the mesh
  uint32_t _vao{ };
  // vertex buffer object - holds raw vertex_t data
  uint32_t _vbo{ };
  // index buffer object - holds indice data
  uint32_t _ebo{ };
public:
  Mesh(std::vector<vertex_t> vertex, std::vector<uint32_t> indices);

  void bind();
  void render(glm::mat4& model, glm::mat4& view, glm::mat4& proj);
};

#endif // !_MESH_H_
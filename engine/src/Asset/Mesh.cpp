#include <Asset/Mesh.h>
#include <Utility/GLConfig.h>

Mesh::Mesh(std::vector<vertex_t> vertexes, std::vector<uint32_t> indices)
  : _vertex(std::move(vertexes)), _indices(std::move(indices))
{
  glGenVertexArrays(1, &_vao);
  glBindVertexArray(_vao);

  glGenBuffers(1, &_ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(uint32_t), _indices.data(), GL_STATIC_DRAW);

  glGenBuffers(1, &_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferData(GL_ARRAY_BUFFER, _vertex.size() * sizeof(vertex_t), _vertex.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, _world));

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, _normal));

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, _tex));


  glm::vec3 min = _vertex[0]._world;
  glm::vec3 max = _vertex[0]._world;

  for (auto& v : _vertex) {
    auto& w = v._world;

    if (min.x > w.x) min.x = w.x;
    if (min.y > w.y) min.y = w.y;
    if (min.z > w.z) min.z = w.z;

    if (max.x < w.x) max.x = w.x;
    if (max.y < w.y) max.y = w.y;
    if (max.z < w.z) max.z = w.z;
  }

  _bounding_box.first = min;
  _bounding_box.second = max;
}

void Mesh::bind()
{
  glBindVertexArray(_vao);
}

void Mesh::render()
{
  bind();
  glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, nullptr);
}
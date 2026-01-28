#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

struct vertex_t {
  glm::vec3 _world_pos;
  glm::vec2 _tex_pos;
};

class BufferArray
{
private:
  unsigned int _buffer_array;
public:
  BufferArray() = default;
  // world coordinate + texture coordinate
  BufferArray(std::vector<vertex_t> positions);

  void bind();

  unsigned int get_id() { return _buffer_array; }
};
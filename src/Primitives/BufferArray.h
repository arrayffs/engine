#pragma once

#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include "../Util/Defines.h"

class BufferArray
{
private:
  unsigned int _buffer_array;
public:
  BufferArray() = default;
  BufferArray(std::vector<vertex_t> positions);

  void bind();

  unsigned int get_id() { return _buffer_array; }
};
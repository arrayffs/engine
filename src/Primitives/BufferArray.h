#pragma once

#include <vector>
#include <glm/vec3.hpp>

class BufferArray
{
private:
  unsigned int _buffer_array;
public:
  BufferArray() = default;
  BufferArray(std::vector<glm::vec3> positions);

  void bind();

  unsigned int get_id() { return _buffer_array; }
};
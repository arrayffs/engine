#pragma once

#include <vector>

class VertexArray {
private:
  unsigned int _vertex_array;
  unsigned int _index_buffer;
public:
  VertexArray() = default;
  VertexArray(std::vector<unsigned int> indices);

  void bind();

  unsigned int get_va_id() { return _vertex_array; }
  unsigned int get_ib_id() { return _index_buffer; }
};
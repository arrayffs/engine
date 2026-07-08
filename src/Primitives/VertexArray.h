#pragma once

#include <vector>

class VertexArray
{
private:
  unsigned int _vertex_array;
  unsigned int _index_buffer;

  size_t _count;
  std::vector<unsigned int> _indices_cache;
public:
  VertexArray() = default;
  VertexArray(std::vector<unsigned int> indices);

  void bind();

  unsigned int get_va_id() const { return _vertex_array; }
  unsigned int get_ib_id() const { return _index_buffer; }

  size_t count() const { return _count; }

  const std::vector<unsigned int>& get_indices_cache() const { return _indices_cache; }
};
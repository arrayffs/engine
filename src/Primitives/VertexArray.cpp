#include "VertexArray.h"

#include <GL/glew.h>

VertexArray::VertexArray(std::vector<unsigned int> ib_indices)
{
  glGenVertexArrays(1, &_vertex_array);
  glBindVertexArray(_vertex_array);
  
  glGenBuffers(1, &_index_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, ib_indices.size() * sizeof(unsigned int), ib_indices.data(), GL_STATIC_DRAW);
}

void VertexArray::bind()
{
  glBindVertexArray(_vertex_array);
}
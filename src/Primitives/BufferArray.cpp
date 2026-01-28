#include "BufferArray.h"

#include <GL/glew.h>

BufferArray::BufferArray(std::vector<vertex_t> positions) {
  glGenBuffers(1, &_buffer_array);
  glBindBuffer(GL_ARRAY_BUFFER, _buffer_array);
  glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(vertex_t), positions.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, _world_pos));

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, _tex_pos));
}

void BufferArray::bind() {
  glBindBuffer(GL_ARRAY_BUFFER, _buffer_array);
}
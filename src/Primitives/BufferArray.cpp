#include "BufferArray.h"

#include <GL/glew.h>

BufferArray::BufferArray(std::vector<glm::vec3> positions) {
  glGenBuffers(1, &_buffer_array);
  glBindBuffer(GL_ARRAY_BUFFER, _buffer_array);
  glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), positions.data(), GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);
}

void BufferArray::bind() {
  glBindBuffer(GL_ARRAY_BUFFER, _buffer_array);
}
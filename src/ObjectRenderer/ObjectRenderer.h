#pragma once

#include <string>
#include <vector>
#include <glm/matrix.hpp>

#include "../Primitives/BufferArray.h"
#include "../Primitives/VertexArray.h"
#include "../Primitives/Program.h"

class ObjectRenderer
{
  BufferArray _buffer_array;
  VertexArray _vertex_array;
  Program _program;

  size_t _element_count;

public:
  ObjectRenderer(std::vector<glm::vec3> positions, std::vector<unsigned int> indices, std::string vertex_shader_path, std::string fragment_shader_path);

  void bind();
  void render(bool autobind = true);

  unsigned int get_buffer_array_id() { return _buffer_array.get_id(); }
  unsigned int get_vertex_array_id() { return _vertex_array.get_va_id(); }
  unsigned int get_index_buffer_id() { return _vertex_array.get_ib_id(); }
  unsigned int get_program_id() { return _program.get_id(); }

  void set_uniform_4f(const char* uniform, float colors[4]);
  void set_uniform_mat4(const char* uniform, glm::mat4 mat);
};
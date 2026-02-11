#pragma once

#include <string>
#include <vector>
#include <glm/matrix.hpp>

#include "../Primitives/BufferArray.h"
#include "../Primitives/VertexArray.h"
#include "../Primitives/Program.h"
#include "../Primitives/Texture.h"

class ObjectRenderer
{
  BufferArray _buffer_array;
  VertexArray _vertex_array;
  Program _program;
  Texture _texture;

  size_t _element_count;
  glm::vec3 _world_pos = glm::vec3(0.f);

public:
  ObjectRenderer() = default;
  ObjectRenderer(std::vector<vertex_t> positions, std::vector<unsigned int> indices, std::string vertex_shader_path, std::string fragment_shader_path, std::string texture_path);

  void bind();
  void render(bool autobind = true);
  void render(glm::mat4& model, glm::mat4& view, glm::mat4& proj);

  unsigned int get_buffer_array_id() { return _buffer_array.get_id(); }
  unsigned int get_vertex_array_id() { return _vertex_array.get_va_id(); }
  unsigned int get_index_buffer_id() { return _vertex_array.get_ib_id(); }
  unsigned int get_program_id() { return _program.get_id(); }

  void set_pos(glm::vec3 world_pos)
  {
	  _world_pos = world_pos;
	  set_uniform_vec3("offset", _world_pos);
  }

  glm::vec3 get_pos() const { return _world_pos; }

  void set_uniform_1i(const char* uniform, int i);
  void set_uniform_4f(const char* uniform, float colors[4]);
  void set_uniform_mat4(const char* uniform, glm::mat4 mat);
  void set_uniform_vec3(const char* uniform, glm::vec3 mat);
};
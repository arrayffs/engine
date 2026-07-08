#pragma once

#include <string>
#include <vector>
#include <glm/matrix.hpp>

#include "../Primitives/BufferArray.h"
#include "../Primitives/VertexArray.h"
#include "../Primitives/Program.h"
#include "../Primitives/Texture.h"

#include "../AssetManager/Material.h"

enum class ObjectType {
  MODEL,
  LIGHT
};

class Mesh
{
  BufferArray _buffer_array;
  VertexArray _vertex_array;
  Program* _program;
  
  Texture _diffuse_tex;
  Texture _specular_tex;
  Texture _normal_tex;

  Material _material;
  bool _has_diffuse = false;
  bool _has_specular = false;
  bool _has_normal = false;

  size_t _element_count;
  glm::vec3 _world_pos = glm::vec3(0.f);
  glm::vec3 _scale = glm::vec3(1.f);
  ObjectType _object_type = ObjectType::MODEL;

  bool _hovered{ false };
public:
  Mesh() = default;
  ~Mesh();
  Mesh(ObjectType object_type, std::vector<vertex_t> positions, std::vector<unsigned int> indices, Program& program, Material material);

  Mesh(const Mesh&) = delete;
  Mesh& operator=(const Mesh&) = delete;

  Mesh(Mesh&&) noexcept = default;
  Mesh& operator=(Mesh&&) noexcept = default;

  void bind();
  bool render(glm::mat4& model, glm::mat4& view, glm::mat4& proj, glm::vec3& light_source, glm::vec3& position);

  unsigned int get_buffer_array_id() { return _buffer_array.get_id(); }
  unsigned int get_vertex_array_id() { return _vertex_array.get_va_id(); }
  unsigned int get_index_buffer_id() { return _vertex_array.get_ib_id(); }
  unsigned int get_program_id() { return _program->get_id(); }

  void set_pos(glm::vec3 world_pos)
  {
    _world_pos = world_pos;
    set_uniform_vec3("u_offset", _world_pos);
  }

  glm::vec3 get_pos() const { return _world_pos; }

  void set_scale(glm::vec3 scale)
  {
    _scale = scale;
    set_uniform_vec3("u_scale", _scale);
  }

  glm::vec3 get_scale() const { return _scale; }


  void set_uniform_1f(const char* uniform, float i);
  void set_uniform_1i(const char* uniform, int i);
  void set_uniform_4f(const char* uniform, float colors[4]);
  void set_uniform_mat4(const char* uniform, glm::mat4 mat);
  void set_uniform_vec3(const char* uniform, glm::vec3 mat);

  const BufferArray& get_buffer_array() const { return _buffer_array; }
  const VertexArray& get_vertex_array() const { return _vertex_array; }

  void set_hovered(bool state) { _hovered = state; }
  bool is_hovered() const { return _hovered; }
};
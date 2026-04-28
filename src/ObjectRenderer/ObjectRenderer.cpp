#include "ObjectRenderer.h"

#include "../Util/Defines.h"

#include "../Util/GLConfig.h"
#include <glm/ext.hpp>

Mesh::Mesh(ObjectType object_type, std::vector<vertex_t> positions, std::vector<unsigned int> indices, Program& program, Material material)
{
  _vertex_array = VertexArray(indices);
  _buffer_array = BufferArray(positions);
  _program = &program;
  _element_count = indices.size();
  _material = material;
  _object_type = object_type;

  if (!material.diffuse_tex.empty()) {
    _diffuse_tex = Texture(GL_TEXTURE_2D, material.diffuse_tex);
    _has_diffuse = true;
  }
  if (!material.specular_tex.empty()) {
    _specular_tex = Texture(GL_TEXTURE_2D, material.specular_tex);
    _has_specular = true;
  }
  if (!material.normal_tex.empty()) {
    _normal_tex = Texture(GL_TEXTURE_2D, material.normal_tex);
    _has_normal = true;
  }

  

  set_uniform_vec3("u_offset", _world_pos);
  set_uniform_vec3("u_scale", { 1.f, 0.5f, 0.5f });
}

void Mesh::bind()
{
  _vertex_array.bind();
  _buffer_array.bind();
  _program->bind();

  // Bind textures to specific slots
  if (_has_diffuse)  _diffuse_tex.bind(GL_TEXTURE0);
  if (_has_specular) _specular_tex.bind(GL_TEXTURE1);
  if (_has_normal)   _normal_tex.bind(GL_TEXTURE2);

  // Upload Material Uniforms
  set_uniform_vec3("u_material.diffuse", _material.diffuse);
  set_uniform_vec3("u_material.ambient", _material.ambient);
  set_uniform_vec3("u_material.specular", _material.specular);
  set_uniform_1f("u_material.shininess", _material.shininess);
  set_uniform_1f("u_material.opacity", _material.opacity);

  // Tell the shader if we are using textures or raw colors
  set_uniform_1i("u_material.has_diffuse_tex", _has_diffuse ? 1 : 0);
  set_uniform_1i("u_material.has_specular_tex", _has_specular ? 1 : 0);
  set_uniform_1i("u_material.has_normal_tex", _has_normal ? 1 : 0);

  // Set sampler slots
  set_uniform_1i("u_material.diffuse_sampler", 0);
  set_uniform_1i("u_material.specular_sampler", 1);
  set_uniform_1i("u_material.normal_sampler", 2);

  unsigned int sampler = glGetUniformLocation(get_program_id(), "u_sampler");
  glUniform1i(sampler, 0);

  unsigned int light_color = glGetUniformLocation(get_program_id(), "u_light_color");
  glm::vec3 light = glm::vec3(1.f, 1.f, 1.f);
  glUniform3fv(light_color, 1, glm::value_ptr(light));
}

void Mesh::render(glm::mat4& model, glm::mat4& view, glm::mat4& proj)
{
  bind();

  set_uniform_mat4("u_model", model);
  set_uniform_mat4("u_view", view);
  set_uniform_mat4("u_proj", proj);

  glDrawElements(GL_TRIANGLES, _element_count, GL_UNSIGNED_INT, nullptr);
}

void Mesh::set_uniform_1f(const char* uniform, float i)
{
  int uniform_id = glGetUniformLocation(_program->get_id(), uniform);
  if (uniform_id != -1)
  glUniform1f(uniform_id, i);
}

void Mesh::set_uniform_1i(const char* uniform, int i)
{
  int uniform_id = glGetUniformLocation(_program->get_id(), uniform);
  if (uniform_id != -1)
  glUniform1i(uniform_id, i);
}

void Mesh::set_uniform_4f(const char* uniform, float colors[4])
{
  int uniform_id = glGetUniformLocation(_program->get_id(), uniform);
  if (uniform_id != -1)
  glUniform4f(uniform_id, colors[0], colors[1], colors[2], colors[3]);
}

void Mesh::set_uniform_mat4(const char* uniform, glm::mat4 mat)
{
  int uniform_id = glGetUniformLocation(_program->get_id(), uniform);
  if (uniform_id != -1)
  glUniformMatrix4fv(uniform_id, 1, GL_FALSE, glm::value_ptr(mat));
}

void Mesh::set_uniform_vec3(const char* uniform, glm::vec3 mat)
{
  int uniform_id = glGetUniformLocation(_program->get_id(), uniform);
  if (uniform_id != -1)
  glUniform3fv(uniform_id, 1, glm::value_ptr(mat));
}
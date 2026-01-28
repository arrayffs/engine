#include "ObjectRenderer.h"

#include "../Util/Defines.h"

#include <GL/glew.h>
#include <glm/ext.hpp>

ObjectRenderer::ObjectRenderer(std::vector<vertex_t> positions, std::vector<unsigned int> indices, std::string vertex_shader_path, std::string fragment_shader_path)
{
  _vertex_array = VertexArray(indices);
  _buffer_array = BufferArray(positions);
  _program = Program(vertex_shader_path, fragment_shader_path);
  _element_count = indices.size();
}

void ObjectRenderer::bind()
{
  _vertex_array.bind();
  _buffer_array.bind();
  _program.bind();
}

void ObjectRenderer::render(bool autobind)
{
  if (autobind)
    bind();
  glDrawElements(GL_TRIANGLES, _element_count, GL_UNSIGNED_INT, nullptr);
}

void ObjectRenderer::set_uniform_1i(const char* uniform, int i)
{
  int uniform_id = glGetUniformLocation(_program.get_id(), uniform);
  assert(uniform_id != -1);
  glUniform1i(uniform_id, i);
}

void ObjectRenderer::set_uniform_4f(const char* uniform, float colors[4])
{
  int uniform_id = glGetUniformLocation(_program.get_id(), uniform);
  assert(uniform_id != -1);
  glUniform4f(uniform_id, colors[0], colors[1], colors[2], colors[3]);
}

void ObjectRenderer::set_uniform_mat4(const char* uniform, glm::mat4 mat)
{
  int uniform_id = glGetUniformLocation(_program.get_id(), uniform);
  assert(uniform_id != -1);
  glUniformMatrix4fv(uniform_id, 1, GL_FALSE, glm::value_ptr(mat));
}
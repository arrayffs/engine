#pragma once

#include "../Util/Defines.h"
#include <mutex>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "../Primitives/BufferArray.h"
#include "../Primitives/VertexArray.h"
#include "../Primitives/Program.h"
#include "../Primitives/Texture.h"
#include "../AssetManager/Material.h"
#include "../AssetManager/Mesh.h"

namespace generator_config {
  inline float min_ceil{ -5.f };
  inline float max_ceil{ 5.f };

  inline float point_density{ 16.f };
}

class Terrain
{
protected:
  Material _material = Material(
    glm::vec3(0.8f),
    glm::vec3(0.2f),
    glm::vec3(0.0f),
    glm::vec3(0.0f),
    250.0f,
    1.0f
  );
  Mesh _mesh;
  Program _program;
 
public:
  Terrain() = default;
  ~Terrain();

  void generate(unsigned int seed, glm::vec2 grid_size = {256.f, 256.f});

  void render(glm::mat4& model, glm::mat4& view, glm::mat4& proj, glm::vec3& light_position, glm::vec3& camera_position);


  void set_uniform_1f(const char* uniform, float i)
  {
    int uniform_id = glGetUniformLocation(_program.get_id(), uniform);
    if (uniform_id != -1)
      glUniform1f(uniform_id, i);
  }

  void set_uniform_1i(const char* uniform, int i)
  {
    int uniform_id = glGetUniformLocation(_program.get_id(), uniform);
    if (uniform_id != -1)
      glUniform1i(uniform_id, i);
  }

  void set_uniform_4f(const char* uniform, float colors[4])
  {
    int uniform_id = glGetUniformLocation(_program.get_id(), uniform);
    if (uniform_id != -1)
      glUniform4f(uniform_id, colors[0], colors[1], colors[2], colors[3]);
  }

  void set_uniform_mat4(const char* uniform, glm::mat4 mat)
  {
    int uniform_id = glGetUniformLocation(_program.get_id(), uniform);
    if (uniform_id != -1)
      glUniformMatrix4fv(uniform_id, 1, GL_FALSE, glm::value_ptr(mat));
  }

  void set_uniform_vec3(const char* uniform, glm::vec3 mat)
  {
    int uniform_id = glGetUniformLocation(_program.get_id(), uniform);
    if (uniform_id != -1)
      glUniform3fv(uniform_id, 1, glm::value_ptr(mat));
  }
};
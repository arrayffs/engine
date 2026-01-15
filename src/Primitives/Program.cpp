#include "Program.h"

#include "../Shader/Shader.h"

#include <GL/glew.h>

Program::Program(const std::string& vs_path, const std::string& fs_path)
{
  std::string fragment_shader = shaders::load_shader(fs_path);
  std::string vertex_shader = shaders::load_shader(vs_path);
  _program = shaders::create_program(vertex_shader, fragment_shader);
  glUseProgram(_program);
}

void Program::bind()
{
  glUseProgram(_program);
}
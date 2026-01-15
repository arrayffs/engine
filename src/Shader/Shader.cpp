#include "Shader.h"

#include <GL/glew.h>

#include <stdexcept>
#include <fstream>
#include <sstream>

std::string shaders::load_shader(const std::string& path) {
  std::ifstream triag_frag_file(path);
  if (!triag_frag_file.is_open())
    throw std::logic_error("File not found: " + path);
  return (std::stringstream() << triag_frag_file.rdbuf()).str();
}

unsigned int shaders::compile_shader(unsigned int SHADER_TYPE, const std::string& source)
{
  unsigned int id = glCreateShader(SHADER_TYPE);
  const char* src = source.c_str();

  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    int len;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
    void* message = alloca(len);
    if (!message)
      return 0;

    glGetShaderInfoLog(id, len, &len, (char*)message);
    glDeleteShader(id);
    throw std::runtime_error(std::string("Failed to compile shader: ") + (const char*)message);
  }

  return id;
}

unsigned int shaders::create_program(const std::string& vertex_shader, const std::string& fragment_shader)
{
  unsigned int program = glCreateProgram();
  unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
  unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

  glAttachShader(program, vs);
  glAttachShader(program, fs);

  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
}

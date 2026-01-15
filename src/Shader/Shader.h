#pragma once

#include <string>

namespace shaders {
  unsigned int compile_shader(unsigned int SHADER_TYPE, const std::string& source);
  
  unsigned int create_program(const std::string& vertex_shader, const std::string& fragment_shader);

  std::string load_shader(const std::string& path);
}
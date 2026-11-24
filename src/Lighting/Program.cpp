#include "Program.h"

#include "ProgramFactory.h"

#include <Utility/GLConfig.h>
#include <Utility/Logger.h>

Program::Program(const std::string& vs_path, const std::string& fs_path)
{
  std::string fragment_shader = program_factory::load_shader(fs_path);
  std::string vertex_shader = program_factory::load_shader(vs_path);
  _program = program_factory::create_program(vertex_shader, fragment_shader);
  glUseProgram(_program);
  Logger::message("Program", "Compiled");
}

void Program::bind()
{
  glUseProgram(_program);
}
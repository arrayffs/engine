#pragma once

#include <string>

class Program
{
private:
  unsigned int _program;
public:
  Program() = default;

  Program(const std::string& vs_path, const std::string& fs_path);
  
  void bind();

  unsigned int get_id() { return _program; }
};
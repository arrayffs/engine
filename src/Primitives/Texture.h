#pragma once

#include <string>

#include <GL/glew.h>

class Texture {
private:
  std::string _file_path{};
  GLenum _texture_target{};
  unsigned int _texture_object{};
  bool _valid_texture{ false };
public:
  Texture() = default;
  Texture(GLenum texture_target, const std::string& file_path);
  
  void bind(unsigned int texture_unit);
};

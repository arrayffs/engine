#include "Texture.h"

#include <print>

#include <stb_image.h>

Texture::Texture(GLenum texture_target, const std::string& file_path)
{
  _texture_target = texture_target;
  _file_path = file_path;

  stbi_set_flip_vertically_on_load(true);
  int width{ 0 }, height{ 0 }, bpp{ 0 };
  unsigned char* image_data = stbi_load(_file_path.c_str(), &width, &height, &bpp, 0);
  if (!image_data) {
    std::println("Texture.cpp:16 - stbi_load() failed.");
    return;
  }
  
  glGenTextures(1, &_texture_object);
  glBindTexture(_texture_target, _texture_object);
  if (_texture_target == GL_TEXTURE_2D)
    glTexImage2D(_texture_target, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
  else {
    std::println("Texture.cpp:25 - Using unsupported texture type! Exitting.\n");
    return;
  }

  glTexParameterf(_texture_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(_texture_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(_texture_target, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(_texture_target, GL_TEXTURE_WRAP_T, GL_CLAMP);

  glBindTexture(_texture_target, 0);
  stbi_image_free(image_data);

  _valid_texture = true;
}

void Texture::bind(unsigned int texture_unit) {
  if (!_valid_texture) {
    std::println("Texture.cpp:40 - Attempted to bind invalid texture!\n");
    return;
  }

  glActiveTexture(texture_unit);
  glBindTexture(_texture_target, _texture_object);
}

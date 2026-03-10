#include "Texture.h"

#include <print>

#include <stb_image.h>

Texture::Texture(GLenum texture_target, const std::string& file_path)
{
  _texture_target = texture_target;
  _file_path = file_path;

  stbi_set_flip_vertically_on_load(true);
  int width{ 0 }, height{ 0 }, bpp{ 0 };
  unsigned char* image_data = stbi_load(_file_path.c_str(), &width, &height, &bpp, 4);
  
  if (!image_data) {
    std::println("Texture.cpp:16 - stbi_load() failed: {}", _file_path);
    return;
  }

  // Determine format based on number of channels
  GLenum format = GL_RGB;
  if (bpp == 4) format = GL_RGBA;
  if (bpp == 1) format = GL_RED;

  glGenTextures(1, &_texture_object);
  glBindTexture(_texture_target, _texture_object);

  // Linux drivers are picky! Set alignment to 1 for RGB textures
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  glTexImage2D(_texture_target, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image_data);

  glTexParameterf(_texture_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(_texture_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

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

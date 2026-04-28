#pragma once

#include "ObjectRenderer.h"

namespace object_loader {
  Mesh load_from_file(const std::string& filepath, const std::string& vert_shader_path, const std::string& frag_shader_path, const std::string& texture_path);
  Mesh load_from_file(const std::string& filepath, glm::vec3 pos, const std::string& vert_shader_path, const std::string& frag_shader_path, const std::string& texture_path);
}
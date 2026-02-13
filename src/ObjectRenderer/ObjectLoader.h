#pragma once

#include "ObjectRenderer.h"

namespace object_loader {
  ObjectRenderer load_from_file(const std::string& filepath);
  ObjectRenderer load_from_file(const std::string& filepath, glm::vec3 pos);
}
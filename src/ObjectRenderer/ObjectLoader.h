#pragma once

#include "ObjectRenderer.h"

namespace object_loader {
  ObjectRenderer load_from_file(const std::string& filepath, glm::vec3 pos = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f));
}
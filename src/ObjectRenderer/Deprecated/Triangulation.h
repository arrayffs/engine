#pragma once

#include "../Util/Defines.h"

#include <vector>

namespace triangulation {
  std::vector<unsigned int> delaunay(const std::vector<vertex_t>& face);
}

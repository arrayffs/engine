#pragma once

#ifndef _DEFINES_H_
#define _DEFINES_H_

#ifdef _MSC_VER
#define assert(x) if (!(x)) __debugbreak();
#else
#error Please define an assert for your compiler in Main.cpp first!
#endif

#include <glm/glm.hpp>

struct vertex_t {
  glm::vec3 _world_pos;
  glm::vec2 _tex_pos;
};

#endif // !_DEFINES_H_
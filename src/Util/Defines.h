#pragma once

#ifndef _DEFINES_H_
#define _DEFINES_H_

#pragma warning (disable: 4005 4244)

#ifdef _MSC_VER
#define assert(x) if (!(x)) __debugbreak();
#elif __unix__
#define assert(x) if (!(x)) raise(SIGTRAP);
#else
#error Please define an assert for your compiler in Main.cpp first!
#endif

#include <glm/glm.hpp>

struct vertex_t {
  glm::vec3 _world_pos;
  glm::vec2 _tex_pos;
  glm::vec3 _normal;
};

#endif // !_DEFINES_H_

#pragma once

#ifdef _MSC_VER
#define assert(x) if (!(x)) __debugbreak();
#else
#error Please define an assert for your compiler in Main.cpp first!
#endif
#pragma once

#ifdef __unix__
    #include <glad/glad.h>
#else
    #define GLEW_STATIC
    #include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

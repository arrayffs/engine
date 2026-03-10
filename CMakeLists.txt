cmake_minimum_required(VERSION 4.0.0)
project(engine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.cc" "src/*.c" "src/*.hpp" "src/*.h")

set(SRC_KEYBOARD
  src/Keyboard/KeybindManager.cpp
)

set(SRC_PRIMITIVES
  src/Primitives/BufferArray.cpp
  src/Primitives/Program.cpp
  src/Primitives/Texture.cpp
  src/Primitives/VertexArray.cpp
)

set(SRC_OBJECT_RENDERER
  src/ObjectRenderer/ObjectLoader.cpp
  src/ObjectRenderer/ObjectRenderer.cpp
)

set(SRC_SHADER
  src/Shader/Shader.cpp
)

set(SRC_UTIL
  src/Util/OrbitalCamera.cpp
  src/Util/stb.cpp
)
set(SRC_WINDOW
  src/Window/Window.cpp
)

add_executable(engine
  src/Main.cpp
  ${SRC_KEYBOARD}
  ${SRC_OBJECT_RENDERER}
  ${SRC_PRIMITIVES}
  ${SRC_SHADER}
  ${SRC_UTIL}
  ${SRC_WINDOW}

  Vendor/glad/src/glad.c 
)

target_include_directories(engine PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/GL/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/GLFW/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/assimp/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/glm/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/stb/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/glad/Include
)

target_link_libraries(engine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/GL/libGLEW.a
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/GLFW/libglfw3.a
    ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/assimp/libassimp.a
    minizip
    z       # Fixes the Assimp "uncompress/inflate" errors
    GL      # Required for OpenGL functions
    X11     # Required by GLFW
    pthread # Required by GLFW/Assimp
    dl      # Required for GLAD/GLEW/GLFW to load drivers
    m       # Math library (often required by GLM/Assimp)
)

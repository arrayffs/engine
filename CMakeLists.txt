cmake_minimum_required(VERSION 3.20)

project(engine
    VERSION 0.1.0
    LANGUAGES C CXX
)

# some configing
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# libs
if(NOT MSVC OR NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL_ERROR "Vendor/ only contains MSVC x64 libraries; configure with the x64 MSVC toolchain.")
endif()

find_package(OpenGL REQUIRED)

add_library(glad STATIC ${VENDOR_DIR}/glad/src/glad.c)
target_include_directories(glad SYSTEM PUBLIC ${VENDOR_DIR}/glad/Include)
set_target_properties(glad PROPERTIES FOLDER "Vendor")

add_library(glew STATIC IMPORTED)
set_target_properties(glew PROPERTIES
    IMPORTED_LOCATION             ${VENDOR_DIR}/GL/glew32s.lib
    INTERFACE_INCLUDE_DIRECTORIES ${VENDOR_DIR}/GL/Include
    INTERFACE_COMPILE_DEFINITIONS GLEW_STATIC
    INTERFACE_LINK_LIBRARIES      OpenGL::GL
    INTERFACE_LINK_OPTIONS        /NODEFAULTLIB:LIBCMT
)

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
    IMPORTED_LOCATION             ${VENDOR_DIR}/GLFW/glfw3.lib
    INTERFACE_INCLUDE_DIRECTORIES ${VENDOR_DIR}/GLFW/Include
    INTERFACE_COMPILE_DEFINITIONS GLFW_INCLUDE_NONE
    INTERFACE_LINK_LIBRARIES      "OpenGL::GL;gdi32;user32;shell32"
    INTERFACE_LINK_OPTIONS        "$<$<CONFIG:Debug>:/NODEFAULTLIB:MSVCRT>"
)

set(ASSIMP_DLL ${VENDOR_DIR}/Assimp/assimp-vc143-mt.dll)
add_library(assimp SHARED IMPORTED)
set_target_properties(assimp PROPERTIES
    IMPORTED_IMPLIB               ${VENDOR_DIR}/Assimp/assimp-vc143-mt.lib
    IMPORTED_LOCATION             ${ASSIMP_DLL}
    INTERFACE_INCLUDE_DIRECTORIES ${VENDOR_DIR}/Assimp/include
)

add_library(glm INTERFACE)
target_include_directories(glm SYSTEM INTERFACE ${VENDOR_DIR}/glm/Include)

add_library(stb INTERFACE)
target_include_directories(stb SYSTEM INTERFACE ${VENDOR_DIR}/stb/Include)

# sources
set(ENGINE_SOURCES
    src/Main.cpp
    src/Engine.cpp
    src/Asset/Mesh.cpp
    src/Lighting/Program.cpp
    src/Lighting/ProgramFactory.cpp
    src/Window/Window.cpp
)

set(ENGINE_HEADERS
    src/Engine.h
    src/Asset/Asset.h
    src/Asset/AssetManager.h
    src/Asset/Mesh.h
    src/Lighting/Program.h
    src/Lighting/ProgramFactory.h
    src/Material/Material.h
    src/Material/MaterialVendor.h
    src/Utility/GLConfig.h
    src/Utility/Logger.h
    src/Utility/Singleton.h
    src/Window/Window.h
)

add_executable(${PROJECT_NAME} ${ENGINE_SOURCES} ${ENGINE_HEADERS})

# linking
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        glad
        glew
        glfw
        assimp
        glm
        stb
        OpenGL::GL
)

if(EXISTS ${ASSIMP_DLL})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${ASSIMP_DLL} $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
else()
    message(WARNING "Missing ${ASSIMP_DLL}: the engine will link, but won't start once it uses Assimp.")
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_CURRENT_SOURCE_DIR}/res
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src
    PREFIX "src"
    FILES ${ENGINE_SOURCES} ${ENGINE_HEADERS}
)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive- /MP)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>)

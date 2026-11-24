set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(ENGINE_SOURCES
    src/Engine.cpp
    src/Asset/Asset.cpp
    src/Asset/AssetManager.cpp
    src/Asset/Mesh.cpp
    src/CorePlugin/Camera/Camera.cpp
    src/CorePlugin/Camera/OrbitalCamera.cpp
    src/GameWorld/BaseObject.cpp
    src/Lighting/Program.cpp
    src/Lighting/ProgramFactory.cpp
    src/Utility/Singleton.cpp
    src/Window/Window.cpp
)

set(ENGINE_HEADERS
    Include/Engine.h
    Include/Asset/Asset.h
    Include/Asset/AssetManager.h
    Include/Asset/Mesh.h
    Include/CorePlugin/Camera/Camera.h
    Include/CorePlugin/Camera/OrbitalCamera.h
    Include/GameWorld/BaseObject.h
    Include/GameWorld/GameWorld.h
    Include/Lighting/Program.h
    Include/Lighting/ProgramFactory.h
    Include/Material/Material.h
    Include/Material/MaterialVendor.h
    Include/Utility/GLConfig.h
    Include/Utility/Logger.h
    Include/Utility/Singleton.h
    Include/Window/Window.h
)

add_library(engine SHARED ${ENGINE_SOURCES} ${ENGINE_HEADERS})

target_include_directories(engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(engine
    PUBLIC
        glm
        glew
        glfw
    PRIVATE
        glad
        assimp
        stb
        OpenGL::GL
)

if(EXISTS ${ASSIMP_DLL})
    add_custom_command(TARGET engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${ASSIMP_DLL} $<TARGET_FILE_DIR:engine>
    )
else()
    message(WARNING "Missing ${ASSIMP_DLL}: the engine will link, but won't start once it uses Assimp.")
endif()

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "src" FILES ${ENGINE_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Include PREFIX "Include" FILES ${ENGINE_HEADERS})

if(MSVC)
    target_compile_options(engine PRIVATE /W4 /permissive- /MP)
    target_compile_options(engine PUBLIC /wd4251)
    target_compile_definitions(engine PRIVATE _CRT_SECURE_NO_WARNINGS)
else()
    target_compile_options(engine PRIVATE -Wall -Wextra -Wpedantic)
endif()
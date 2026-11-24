set(EDITOR_SOURCES
    src/Main.cpp
    src/Keyboard/KeybindManager.cpp
)

set(EDITOR_HEADERS
  src/Keyboard/KeybindManager.h
)

add_executable(editor ${EDITOR_SOURCES} ${EDITOR_HEADERS})

target_include_directories(editor
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(editor
    PRIVATE
        engine
)

add_custom_command(TARGET editor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${RES_DIR}
        $<TARGET_FILE_DIR:editor>/res
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "src" FILES ${EDITOR_SOURCES})

if(MSVC)
    target_compile_options(editor PRIVATE /W4 /permissive- /MP)
    target_compile_definitions(editor PRIVATE _CRT_SECURE_NO_WARNINGS)
else()
    target_compile_options(editor PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(editor PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:editor>)
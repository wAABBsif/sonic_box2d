cmake_minimum_required(VERSION 3.20)
project(sonic_box2d)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DIS_DEBUG")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(IMGUI_FILES)

if (CMAKE_BUILD_TYPE MATCHES Debug)
	set(IMGUI_FILES
			lib/imgui/imconfig.h
			lib/imgui/imgui.cpp
			lib/imgui/imgui.h
			lib/imgui/imgui_demo.cpp
			lib/imgui/imgui_draw.cpp
			lib/imgui/imgui_internal.h
			lib/imgui/imgui_tables.cpp
			lib/imgui/imgui_widgets.cpp
			lib/imgui/imstb_rectpack.h
			lib/imgui/imstb_textedit.h
			lib/imgui/imstb_truetype.h
			lib/imgui/backends/imgui_impl_sdl3.cpp
			lib/imgui/backends/imgui_impl_sdl3.h
			lib/imgui/backends/imgui_impl_opengl3.cpp
			lib/imgui/backends/imgui_impl_opengl3.h
            lib/imgui/misc/cpp/imgui_stdlib.cpp
            lib/imgui/misc/cpp/imgui_stdlib.h
	)
endif ()

set(GLAD_FILES lib/GLAD/src/glad.c)

set(PROJECT_FILES src/main.cpp
    src/game/game.hpp
    src/game/game.cpp
    src/core/log.hpp
    src/core/log.cpp
    src/core/sdl_interface.hpp
    src/core/sdl_interface.cpp
    src/gfx/gfx.hpp
    src/gfx/gfx.cpp
    src/core/time.hpp
    src/core/time.cpp
    src/core/scoped_timer.hpp
    src/core/scoped_timer.cpp
    src/debug/debug_ui.hpp
    src/debug/debug_ui.cpp
    src/debug/stats_window.hpp
    src/debug/stats_window.cpp
    src/game/entity.hpp
    src/game/entity.cpp
    src/debug/entities_window.hpp
    src/debug/entities_window.cpp
    src/game/component.hpp
    src/game/component.cpp
    src/game/components/transform.hpp
    src/game/components/transform.cpp
    src/debug/components_window.hpp
    src/debug/components_window.cpp
    src/core/transformations.hpp
    src/core/transformations.cpp
    src/core/asset.hpp
    src/core/asset.cpp
    src/gfx/shader.hpp
    src/gfx/shader.cpp
    src/gfx/texture.hpp
    src/gfx/texture.cpp
    src/gfx/renderer.hpp
    src/gfx/renderer.cpp
    src/game/components/sprite.hpp
    src/game/components/sprite.cpp
    src/core/color.hpp
    src/core/color.cpp
    src/core/singleton.hpp
    src/game/system.hpp
    src/game/system.cpp
    src/game/systems/sprite_manager.hpp
    src/game/systems/sprite_manager.cpp
)

add_executable(${PROJECT_NAME}
    ${PROJECT_FILES}
    ${GLAD_FILES}
    ${IMGUI_FILES}
)

include_directories(src)
include_directories(lib)
include_directories(lib/imgui)

add_subdirectory(lib/SDL EXCLUDE_FROM_ALL)
include_directories(lib/SDL/include)
target_link_libraries(${PROJECT_NAME} SDL3::SDL3)

find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)

include_directories(lib/GLAD/include)

if (WIN32)
	add_library(OpenAL STATIC IMPORTED)
	set_target_properties(OpenAL PROPERTIES
			IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/AL/OpenAL32.lib"
	)
	target_link_libraries(${PROJECT_NAME} OpenAL)
else ()
	find_package(OpenAL CONFIG REQUIRED)
	target_link_libraries(${PROJECT_NAME} OpenAL::OpenAL)
endif ()

include_directories(lib/glm)

add_subdirectory(lib/box2d)
target_link_libraries(${PROJECT_NAME} box2d)
include_directories(lib/box2d/include)

if (WIN32)
	set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

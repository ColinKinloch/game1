cmake_minimum_required (VERSION 2.8)
project (game1)

add_executable(game1 Game.cpp)
add_library(Window Window.cpp)
add_library(Input Input.cpp)
add_library(Texture Texture.cpp)
add_library(Sprite Sprite.cpp)
add_library(Shader Shader.cpp)
add_library(String String.cpp)

file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_definitions("-std=gnu++11")
add_definitions("-g")

find_package(Freetype)
if(FREETYPE_FOUND)
	include_directories(${FREETYPE_INCLUDE_DIRS})
	target_link_libraries(game1 ${FREETYPE_LIBRARIES})
	target_link_libraries(String ${FREETYPE_LIBRARIES})
endif(FREETYPE_FOUND)
target_link_libraries(game1 SDL2)
target_link_libraries(game1 Window Input Texture Sprite Shader String)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
if(OPENGL_FOUND)
	include_directories(${OPENGL_INCLUDE_DIRS})
	target_link_libraries(Window ${OPENGL_LIBRARIES})
endif(OPENGL_FOUND)
if(GLEW_FOUND)
	include_directories(${GLEW_INCLUDE_DIRS})
	target_link_libraries(Window ${GLEW_LIBRARIES})
endif(GLEW_FOUND)

find_package(DevIL)
if(IL_FOUND)
	include_directories(${IL_INCLUDE_DIR})
	target_link_libraries(Texture ${IL_LIBRARIES})
	target_link_libraries(Texture ${ILU_LIBRARIES})
endif(IL_FOUND)

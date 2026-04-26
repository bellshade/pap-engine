cmake_minimum_required(VERSION 3.16)
project(papGame)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(papEngine
  src/main.cpp

  # engine
  src/engine/mesin_engine.cpp

  # sistem
  src/sistem/window.cpp
  src/sistem/input.cpp

  # rendering
  src/rendering/renderer.cpp

  # camera
  src/camera/camera.cpp

  # core
  src/core/time.cpp
)

target_link_libraries(papEngine glfw OpenGL GLEW)

cmake_minimum_required(VERSION 3.20)
project(Reblocked LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)

include(Dependencies.cmake)
Reblocked_setup_dependencies()

add_executable(Reblocked
  src/gl.c
  src/main.cpp
  src/Window.cpp
  src/Application.cpp
  src/InputManager.cpp
  src/GameStateMachine.cpp
  src/Renderer.cpp
  src/ShaderProgram.cpp
  src/Mesh.cpp
  src/MeshBuilder.cpp
  src/Camera.cpp
  src/TestState.cpp
)

target_include_directories(Reblocked PRIVATE include)

target_link_libraries(Reblocked PRIVATE
  SDL3::SDL3-static
  OpenGL::GL
  glm::glm
)

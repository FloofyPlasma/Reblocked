add_library(ReblockedEngine STATIC
    Graphics/Mesh.cpp
    Graphics/Camera.cpp
    Graphics/MeshBuilder.cpp
    Graphics/Shader.cpp
    Graphics/Renderer.cpp
    gl.c
    State/GameStateMachine.cpp
    Core/Window.cpp
    Core/Application.cpp
    Core/InputManager.cpp
)

target_include_directories(ReblockedEngine PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(ReblockedEngine PUBLIC ${PROJECT_SOURCE_DIR}/include/engine)

target_link_libraries(ReblockedEngine PUBLIC
    SDL3::SDL3-static
    OpenGL::GL
    glm::glm
)

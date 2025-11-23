add_library(ReblockedGame STATIC
    states/TestState.cpp

    World/Grid.cpp
    World/Piece.cpp

    Rendering/GridRenderer.cpp
    Rendering/PieceRenderer.cpp

    Gameplay/CollisionDetector.cpp
)

target_include_directories(ReblockedGame PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(ReblockedGame PUBLIC ${PROJECT_SOURCE_DIR}/include/game)
target_link_libraries(ReblockedGame PUBLIC ReblockedEngine)

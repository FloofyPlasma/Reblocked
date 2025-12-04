add_library(ReblockedGame STATIC
    States/TestState.cpp
    States/PlayingState.cpp

    World/Grid.cpp
    World/Piece.cpp
    World/PieceFactory.cpp

    Rendering/GridRenderer.cpp
    Rendering/PieceRenderer.cpp

    Gameplay/CollisionDetector.cpp
)

target_include_directories(ReblockedGame PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(ReblockedGame PUBLIC ${PROJECT_SOURCE_DIR}/include/game)
target_link_libraries(ReblockedGame PUBLIC ReblockedEngine)

include(cmake/CPM.cmake)
CPMUsePackageLock(package-lock.cmake)

function(Reblocked_setup_dependencies)
  if (NOT TARGET SDL3::SDL3-static)
    cpmaddpackage(
      URI "gh:libsdl-org/SDL#release-3.2.26"
      OPTIONS "SDL_STATIC ON" "SDL_SHARED OFF"
    )
  endif()

  if (NOT TARGET glm::glm)
    cpmaddpackage(
      URI "gh:g-truc/glm#1.0.2"
    )
  endif()

  cpmaddpackage(
    NAME Ccache.cmake
    GITHUB_REPOSITORY TheLartians/Ccache.cmake
    VERSION 1.2.5
  )
endfunction()

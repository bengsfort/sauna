cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(Sauna)

# Todo: Add a way to build the game and editor separately

# Enable cpp
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
# -----------------------------
# This is here as reference; however it isn't being used.
# Instead we use a submodule to fetch raylib, as it gives us more
# control over the version we use and the build process.
#
# set(RAYLIB_VERSION 5.5)
# find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED

# if (NOT raylib_FOUND) # If there's none, fetch and build raylib
#   include(FetchContent)
#   FetchContent_Declare(
#     raylib
#     DOWNLOAD_EXTRACT_TIMESTAMP OFF
#     URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
#   )
#   FetchContent_GetProperties(raylib)
#   if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
#     set(FETCHCONTENT_QUIET NO)
#     FetchContent_Populate(raylib)
#     set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
#     add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
#   endif()
# endif()

# Shared Resources
set(GAME_CONTENT_RESOURCES ${CMAKE_SOURCE_DIR}/src/game_content/resources)

# Sources
option(BUILD_EDITOR "Build the editor executable" ON)
option(BUILD_GAME "Build the game executable" ON)
set(raylib_VERBOSE 1)

add_subdirectory(src/core)
add_subdirectory(src/game_content)
add_subdirectory(third_party/raylib)

if (BUILD_EDITOR)
	message("Editor WILL be built")
	add_subdirectory(src/editor)
else()
	message("Editor will NOT be built")
endif()

if (BUILD_GAME)
	message("Game WILL be built")
	add_subdirectory(src/game)
else()
	message("Game will NOT be built")
endif()

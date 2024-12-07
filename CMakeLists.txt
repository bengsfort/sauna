cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(Sauna)

# Todo: Add a way to build the game and editor separately

# Enable cpp
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED

if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

set(raylib_VERBOSE 1)

# add_subdirectory(third_party/raylib)
# add_subdirectory(source)s

# Resources
set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)
add_custom_target(copy_resources ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${RESOURCES_DIR} ${CMAKE_BINARY_DIR}/resources
	COMMENT "Copying resources to build directory"
)

# Sources
option(BUILD_EDITOR "Build the editor executable" ON)
option(BUILD_GAME "Build the game executable" ON)

add_subdirectory(src/core)

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

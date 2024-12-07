file(GLOB_RECURSE GAME_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/source/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/source/*.hpp
	${CMAKE_CURRENT_LIST_DIR}/source/*.h
)

add_executable(SaunaGame ${GAME_SOURCES})

target_link_libraries(SaunaGame raylib SaunaCore)

target_include_directories(SaunaGame PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
set_target_properties(SaunaGame PROPERTIES OUTPUT_NAME "SaunaGame")

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(SaunaGame "-framework IOKit")
    target_link_libraries(SaunaGame "-framework Cocoa")
    target_link_libraries(SaunaGame "-framework OpenGL")
endif()

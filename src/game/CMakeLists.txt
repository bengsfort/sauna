file(GLOB_RECURSE GAME_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/source/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/source/*.h
	${CMAKE_CURRENT_LIST_DIR}/source/*.hpp
	${CMAKE_CURRENT_LIST_DIR}/source/**/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/source/**/*.hpp
	${CMAKE_CURRENT_LIST_DIR}/source/**/*.h
)

add_executable(SaunaGame ${GAME_SOURCES})

target_link_libraries(SaunaGame SaunaCore SaunaGameContent)

# Resources
set(GAME_RESOURCES_DIR ${CMAKE_CURRENT_LIST_DIR}/resources)
add_custom_target(CopySaunaGameResources ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${GAME_RESOURCES_DIR} $<TARGET_FILE_DIR:SaunaGame>/resources
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${GAME_CONTENT_RESOURCES} $<TARGET_FILE_DIR:SaunaGame>/resources
	COMMENT "Copying game resources to build directory"
)

# Properties and includes
target_include_directories(SaunaGame PRIVATE ${CMAKE_CURRENT_LIST_DIR}/source)
set_target_properties(SaunaGame PROPERTIES OUTPUT_NAME "SaunaGame" LINKER_LANGUAGE CXX CXX_STANDARD 20)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(SaunaGame "-framework IOKit")
    target_link_libraries(SaunaGame "-framework Cocoa")
    target_link_libraries(SaunaGame "-framework OpenGL")
endif()

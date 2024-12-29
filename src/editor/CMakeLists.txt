file(GLOB_RECURSE EDITOR_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/source/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/source/*.hpp
	${CMAKE_CURRENT_LIST_DIR}/source/*.h
)

add_executable(SaunaEditor ${EDITOR_SOURCES})

target_link_libraries(SaunaEditor SaunaCore SaunaGameContent)

# Resources
set(EDITOR_RESOURCES_DIR ${CMAKE_CURRENT_LIST_DIR}/resources)
add_custom_target(CopySaunaEditorResources ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${EDITOR_RESOURCES_DIR} $<TARGET_FILE_DIR:SaunaEditor>/resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${GAME_CONTENT_RESOURCES} $<TARGET_FILE_DIR:SaunaEditor>/resources
    COMMENT "Copying game resources to build directory"
)

target_include_directories(SaunaEditor PRIVATE ${CMAKE_CURRENT_LIST_DIR}/source)
set_target_properties(SaunaEditor PROPERTIES OUTPUT_NAME "SaunaEditor" LINKER_LANGUAGE CXX CXX_STANDARD 20)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(SaunaEditor "-framework IOKit")
    target_link_libraries(SaunaEditor "-framework Cocoa")
    target_link_libraries(SaunaEditor "-framework OpenGL")
endif()

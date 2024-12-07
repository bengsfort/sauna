file(GLOB_RECURSE EDITOR_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/source/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/source/*.hpp
	${CMAKE_CURRENT_LIST_DIR}/source/*.h
)

add_executable(SaunaEditor ${EDITOR_SOURCES})

target_link_libraries(SaunaEditor raylib SaunaCore)

target_include_directories(SaunaEditor PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
set_target_properties(SaunaEditor PROPERTIES OUTPUT_NAME "SaunaEditor")

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(SaunaEditor "-framework IOKit")
    target_link_libraries(SaunaEditor "-framework Cocoa")
    target_link_libraries(SaunaEditor "-framework OpenGL")
endif()

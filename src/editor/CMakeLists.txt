file(GLOB_RECURSE EDITOR_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/source/**/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/source/**/*.hpp
	${CMAKE_CURRENT_LIST_DIR}/source/**/*.h
)

add_executable(SaunaEditor ${EDITOR_SOURCES})

target_link_libraries(SaunaEditor raylib PRIVATE SaunaCore)
target_include_directories(SaunaEditor PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
set_target_properties(SaunaEditor PROPERTIES OUTPUT_NAME "SaunaEditor")

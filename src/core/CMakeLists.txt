file(GLOB_RECURSE CORE_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/core_lib/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/core_lib/*.hpp
	${CMAKE_CURRENT_LIST_DIR}/core_lib/*.h
)

message("CORE_SOURCES: ${CORE_SOURCES}")

add_library(SaunaCore STATIC ${CORE_SOURCES})

target_link_libraries(SaunaCore raylib)
target_include_directories(SaunaCore PUBLIC ${CMAKE_CURRENT_LIST_DIR})
set_target_properties(SaunaCore PROPERTIES LINKER_LANGUAGE CXX)

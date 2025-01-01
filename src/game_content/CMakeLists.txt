file(GLOB_RECURSE GAME_CONTENT_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/content/**/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/content/**/*.hpp
	${CMAKE_CURRENT_LIST_DIR}/content/**/*.h
)

add_library(SaunaGameContent STATIC ${GAME_CONTENT_SOURCES})

target_link_libraries(SaunaGameContent SaunaCore)
target_include_directories(SaunaGameContent PUBLIC ${CMAKE_CURRENT_LIST_DIR})
set_target_properties(SaunaGameContent PROPERTIES LINKER_LANGUAGE CXX CXX_STANDARD 20)

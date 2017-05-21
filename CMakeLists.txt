cmake_minimum_required (VERSION 3.9)
set (CMAKE_POSITION_INDEPENDENT_CODE on)
set (CMAKE_INTERPROCEDURAL_OPTIMIZATION on)
project (foo)
add_library (foo
	src/chkadd.c
	src/chkuadd.c
	src/filesize.c
	src/gets.c
	src/gopt.c
	src/queue.c
	src/stack.c
)

set (CMAKE_C_FLAGS "-O2 -Wall -fstack-protector-strong -D__FORTIFY_SOURCE=2 ${CMAKE_C_FLAGS}")

target_include_directories (foo
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

install (TARGETS foo DESTINATION lib EXPORT foo)
install (DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)
export (EXPORT foo FILE libfoo.cmake)

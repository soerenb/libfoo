cmake_minimum_required (VERSION 3.9)
set (CMAKE_POSITION_INDEPENDENT_CODE on)
set (CMAKE_INTERPROCEDURAL_OPTIMIZATION on)
project (foo)

option (BUILD_TESTING "Enable tests")

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

if (BUILD_TESTING)
	enable_testing ()

	# test stack
	add_executable (test_exec_stack
		tests/stack/stack.c
	)
	target_link_libraries (test_exec_stack
		foo
	)

	add_test (NAME test_stack COMMAND test_exec_stack)

	# test queue
	add_executable (test_exec_queue
		tests/queue/queue.c
	)
	target_link_libraries (test_exec_queue
		foo
	)

	add_test (NAME test_queue COMMAND test_exec_queue)
endif ()

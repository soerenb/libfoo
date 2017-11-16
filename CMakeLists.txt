cmake_minimum_required (VERSION 3.9)
project (foo)

set (CMAKE_POSITION_INDEPENDENT_CODE on)
set (CMAKE_INTERPROCEDURAL_OPTIMIZATION on)
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
endif()

option (BUILD_TESTING "Enable tests")

set (GOL_CFLAGS -Wall -fstack-protector-strong)
set (GOL_CFLAGS_DEBUG ${GOL_CFLAGS} -O0 -ggdb3)
set (GOL_CFLAGS_RELEASE ${GOL_CFLAGS} -O2 -D__FORTIFY_SOURCE=2)
set (GOL_CFLAGS_RELWDBG ${GOL_CFLAGS_RELEASE} -ggdb3)

add_library (foo
	src/chkadd.c
	src/chkuadd.c
	src/filesize.c
	src/gets.c
	src/gopt.c
	src/queue.c
	src/stack.c
)

target_include_directories (foo
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options (foo
	PRIVATE $<$<CONFIG:Debug>:${GOL_CFLAGS_DEBUG}>
	PRIVATE $<$<CONFIG:Release>:${GOL_CFLAGS_RELEASE}>
	PRIVATE $<$<CONFIG:RelWithDebInfo>:${GOL_CFLAGS_RELWDBG}>
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

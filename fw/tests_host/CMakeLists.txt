cmake_minimum_required(VERSION 3.16)
project(tests_host C)
enable_testing()

set(CMAKE_C_STANDARD 99)

set(root_dir ${CMAKE_SOURCE_DIR}/..)
set(unity_dir ${root_dir}/external/Unity/src)
set(lib_dir ${root_dir}/lib)

include_directories(${root_dir} ${lib_dir} ${unity_dir} .)

add_executable(tests_host test_timer_list.c ${lib_dir}/timer_list.c panic.c ${unity_dir}/unity.c)

add_test(NAME tests_host COMMAND tests_host)

add_executable(alarmist
  main.c
  ${root_dir}/lib/clocks_etc.c
  ${root_dir}/lib/stack_check.c
  ${root_dir}/lib/debug.c
  ${root_dir}/lib/panic.c
  ${root_dir}/lib/sys_time.c
  ${root_dir}/lib/event_queue.c
  ${root_dir}/lib/loop.c
  )

add_options(alarmist)
target_include_directories(alarmist BEFORE PUBLIC .)
#target_compile_definitions(alarmist PUBLIC -DNDEBUG)

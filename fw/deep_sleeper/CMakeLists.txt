add_executable(deep_sleeper
  main.c
  ${root_dir}/lib/clocks_etc.c
  ${root_dir}/lib/stack_check.c
  ${root_dir}/lib/debug.c
  ${root_dir}/lib/panic.c
  ${root_dir}/lib/sys_time.c
  ${root_dir}/lib/event_queue.c
  ${root_dir}/lib/timer_list.c
  ${root_dir}/lib/timers.c
  ${root_dir}/lib/loop.c
  ${root_dir}/lib/blinker.c
  ${root_dir}/lib/debouncer.c
  ${root_dir}/lib/button.c 
  )

add_options(deep_sleeper)
target_include_directories(deep_sleeper BEFORE PUBLIC .)

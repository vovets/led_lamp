add_executable(adc_blinker
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
  ${root_dir}/lib/adc.c
  ${root_dir}/lib/adc_filter.c
  )

add_options(adc_blinker)
target_include_directories(adc_blinker BEFORE PUBLIC .)

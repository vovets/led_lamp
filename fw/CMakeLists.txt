cmake_minimum_required(VERSION 3.20)
project(led_lamp C)

set(CMAKE_C_STANDARD 99)
set(F_CPU 8000000)
set(ST_FREQ_DIVIDER 1024)

function(add_misc_targets target)
    get_target_property(dir ${target} BINARY_DIR)
    add_custom_target(${target}.size ALL DEPENDS ${target} COMMAND ${CMAKE_SIZE} -C "${dir}/${target}")
    add_custom_target(${target}.hex ALL DEPENDS ${target} ${target}.size COMMAND ${CMAKE_OBJCOPY} -Oihex "${dir}/${target}" "${dir}/${target}.hex")
    add_custom_target(${target}.bin ALL DEPENDS ${target} COMMAND ${CMAKE_OBJCOPY} -Obinary "${dir}/${target}" "${dir}/${target}.bin")
endfunction()

function(add_flash_target target)
    get_target_property(dir ${target} BINARY_DIR)
    add_custom_target(${target}.flash DEPENDS ${target}.hex
            COMMAND avrdude -c dragon_dw -p attiny85 -u -U flash:w:${target}.hex:i)
endfunction()

function(add_options target)
    target_compile_options(${target} PUBLIC -funsigned-char -funsigned-bitfields -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall)
    target_compile_options(${target} PUBLIC -Og -gdwarf-4 -g3)
    target_compile_options(${target} PUBLIC -mmcu=attiny85)
    target_link_libraries(${target} PUBLIC -mmcu=attiny85 -Wl,-Map="${target}.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -Wl,--defsym=__heap_end=__heap_start)
    #target_link_libraries(${target} PUBLIC -mmcu=attiny85 -Wl,-Map="${target}.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -Wl,--verbose)

    add_misc_targets(${target})
    add_flash_target(${target})
endfunction()

function(add_freq_options target f_cpu st_freq_divider)
    target_compile_definitions(${target} PUBLIC -DF_CPU=${f_cpu} -DST_FREQ_DIVIDER=${st_freq_divider})
endfunction()


add_executable(alarmist alarmist_main.c timers.c clocks_etc.c abort.c stack_check.c debug.c)
add_options(alarmist)
add_freq_options(alarmist 1000000 1024)

add_executable(blinker blinker_main.c blinker.c timers.c clocks_etc.c abort.c stack_check.c debug.c)
add_options(blinker)
add_freq_options(blinker ${F_CPU} ${ST_FREQ_DIVIDER})

add_executable(sleeper sleeper_main.c blinker.c timers.c clocks_etc.c abort.c stack_check.c debug.c)
add_options(sleeper)
add_freq_options(sleeper ${F_CPU} ${ST_FREQ_DIVIDER})

add_executable(adc_blinker adc_blinker_main.c adc.c adc_filter.c blinker.c timers.c clocks_etc.c abort.c stack_check.c)
add_options(adc_blinker)
add_freq_options(adc_blinker ${F_CPU} ${ST_FREQ_DIVIDER})

add_executable(deep_sleeper deep_sleeper_main.c blinker.c timers.c clocks_etc.c abort.c stack_check.c debug.c debouncer.c button.c)
add_options(deep_sleeper)
add_freq_options(deep_sleeper 1000000 1024)

add_executable(lamp lamp_main.c blinker.c alarm.c timers.c clocks_etc.c abort.c stack_check.c debug.c debouncer.c button.c pwm.c vcc_monitor.c adc.c adc_filter.c)
add_options(lamp)
add_freq_options(lamp 1000000 1024)

cmake_minimum_required(VERSION 3.16)
project(led_lamp C)

set(CMAKE_C_STANDARD 99)

set(root_dir ${CMAKE_SOURCE_DIR})


function(add_misc_targets target)
    get_target_property(dir ${target} BINARY_DIR)
    add_custom_target(${target}.size ALL DEPENDS ${target} COMMAND ${CMAKE_SIZE} -G "${dir}/${target}")
    add_custom_target(${target}.hex ALL DEPENDS ${target} ${target}.size COMMAND ${CMAKE_OBJCOPY} -Oihex "${dir}/${target}" "${dir}/${target}.hex")
    add_custom_target(${target}.bin ALL DEPENDS ${target} COMMAND ${CMAKE_OBJCOPY} -Obinary "${dir}/${target}" "${dir}/${target}.bin")
endfunction()


function(add_flash_target target)
    get_target_property(dir ${target} BINARY_DIR)
    add_custom_target(${target}.flash
            DEPENDS ${target}.hex
            COMMAND avrdude -c dragon_dw -p attiny85 -u -U flash:w:${target}.hex:i
            USES_TERMINAL)
endfunction()


function(add_options target)
    target_compile_options(${target} PUBLIC -funsigned-char -funsigned-bitfields -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall)
    target_compile_options(${target} PUBLIC -O3 -gdwarf-4 -g3)
    target_compile_options(${target} PUBLIC -mmcu=attiny85)
    target_link_libraries(${target} PUBLIC -mmcu=attiny85 -Wl,-Map="${target}.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -Wl,--defsym=__heap_end=__heap_start)
    #target_link_libraries(${target} PUBLIC -mmcu=attiny85 -Wl,-Map="${target}.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -Wl,--verbose)

    add_misc_targets(${target})
    add_flash_target(${target})
endfunction()

include_directories(.)

add_subdirectory(alarmist)

add_subdirectory(blinker)

add_subdirectory(sleeper)

add_subdirectory(adc_blinker)

add_subdirectory(deep_sleeper)

add_subdirectory(lamp)

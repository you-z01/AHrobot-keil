# groups.cmake

# group Startup
add_library(Group_Startup OBJECT
  "${SOLUTION_ROOT}/Libraries/CMSIS/startup_stm32f40_41xxx.s"
)
target_include_directories(Group_Startup PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_Startup PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Group_Startup PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Startup PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)
set(COMPILE_DEFINITIONS
  __MICROLIB
  STM32F407xx
)
cbuild_set_defines(AS_ARM COMPILE_DEFINITIONS)
set_source_files_properties("${SOLUTION_ROOT}/Libraries/CMSIS/startup_stm32f40_41xxx.s" PROPERTIES
  COMPILE_FLAGS "${COMPILE_DEFINITIONS}"
)
set_source_files_properties("${SOLUTION_ROOT}/Libraries/CMSIS/startup_stm32f40_41xxx.s" PROPERTIES
  COMPILE_OPTIONS "-masm=auto"
)

# group StdPeriph_Driver
add_library(Group_StdPeriph_Driver OBJECT
  "${SOLUTION_ROOT}/Libraries/STM32F4xx_StdPeriph_Driver/src/misc.c"
  "${SOLUTION_ROOT}/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c"
  "${SOLUTION_ROOT}/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c"
  "${SOLUTION_ROOT}/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c"
  "${SOLUTION_ROOT}/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c"
  "${SOLUTION_ROOT}/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c"
  "${SOLUTION_ROOT}/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c"
  "${SOLUTION_ROOT}/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c"
)
target_include_directories(Group_StdPeriph_Driver PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_StdPeriph_Driver PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Group_StdPeriph_Driver PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_StdPeriph_Driver PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# group CMSIS
add_library(Group_CMSIS OBJECT
  "${SOLUTION_ROOT}/Libraries/CMSIS/system_stm32f4xx.c"
)
target_include_directories(Group_CMSIS PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_CMSIS PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Group_CMSIS PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_CMSIS PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# group FreeRTOS_core
add_library(Group_FreeRTOS_core OBJECT
  "${SOLUTION_ROOT}/FreeRTOS/croutine.c"
  "${SOLUTION_ROOT}/FreeRTOS/event_groups.c"
  "${SOLUTION_ROOT}/FreeRTOS/list.c"
  "${SOLUTION_ROOT}/FreeRTOS/queue.c"
  "${SOLUTION_ROOT}/FreeRTOS/tasks.c"
  "${SOLUTION_ROOT}/FreeRTOS/timers.c"
)
target_include_directories(Group_FreeRTOS_core PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_FreeRTOS_core PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Group_FreeRTOS_core PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_FreeRTOS_core PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# group FreeRTOS_port
add_library(Group_FreeRTOS_port OBJECT
  "${SOLUTION_ROOT}/FreeRTOS/portable/MemMang/heap_4.c"
  "${SOLUTION_ROOT}/FreeRTOS/portable/RVDS/ARM_CM4F/port.c"
)
target_include_directories(Group_FreeRTOS_port PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_FreeRTOS_port PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Group_FreeRTOS_port PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_FreeRTOS_port PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# group Public
add_library(Group_Public OBJECT
  "${SOLUTION_ROOT}/Public/system.c"
  "${SOLUTION_ROOT}/Public/SysTick.c"
  "${SOLUTION_ROOT}/Public/uart.c"
)
target_include_directories(Group_Public PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_Public PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Group_Public PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Public PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# group Peripheral_Driver
add_library(Group_Peripheral_Driver OBJECT
  "${SOLUTION_ROOT}/Peripheral_Driver/led.c"
  "${SOLUTION_ROOT}/Peripheral_Driver/oled.c"
  "${SOLUTION_ROOT}/Peripheral_Driver/usart.c"
  "${SOLUTION_ROOT}/Peripheral_Driver/iic.c"
  "${SOLUTION_ROOT}/Peripheral_Driver/encodeMotor.c"
  "${SOLUTION_ROOT}/Peripheral_Driver/steerEngine.c"
  "${SOLUTION_ROOT}/Peripheral_Driver/stepMotor.c"
)
target_include_directories(Group_Peripheral_Driver PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_Peripheral_Driver PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Group_Peripheral_Driver PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Peripheral_Driver PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# group App
add_library(Group_App OBJECT
  "${SOLUTION_ROOT}/App/encodingMotor.c"
  "${SOLUTION_ROOT}/App/pid.c"
  "${SOLUTION_ROOT}/App/steppingMotor.c"
  "${SOLUTION_ROOT}/App/steeringEngine.c"
)
target_include_directories(Group_App PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_App PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Group_App PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_App PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# group Task
add_library(Group_Task OBJECT
  "${SOLUTION_ROOT}/Task/Bluetooth_control.c"
)
target_include_directories(Group_Task PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_Task PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Group_Task PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_Task PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

# group User
add_library(Group_User OBJECT
  "${SOLUTION_ROOT}/User/main.c"
  "${SOLUTION_ROOT}/User/stm32f4xx_it.c"
)
target_include_directories(Group_User PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_INCLUDE_DIRECTORIES>
)
target_compile_definitions(Group_User PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_DEFINITIONS>
)
target_compile_options(Group_User PUBLIC
  $<TARGET_PROPERTY:${CONTEXT},INTERFACE_COMPILE_OPTIONS>
)
target_link_libraries(Group_User PUBLIC
  ${CONTEXT}_ABSTRACTIONS
)

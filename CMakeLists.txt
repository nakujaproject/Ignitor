cmake_minimum_required(VERSION 3.14)

# Set the project name
project(Microcontroller_Project)

# Common source files
set(COMMON_SOURCES
    src/main.cpp
    src/utilities.cpp
    include/utilities.h
)

# CMake for RTOS (FreeRTOS)
add_executable(FreeRTOS_Project ${COMMON_SOURCES})
target_include_directories(FreeRTOS_Project PRIVATE path/to/FreeRTOS/Source/include)
target_link_libraries(FreeRTOS_Project path/to/FreeRTOS/Source/libFreeRTOS.a)

# CMake for HAL (STM32Cube)
add_executable(STM32Cube_Project ${COMMON_SOURCES})
target_include_directories(STM32Cube_Project PRIVATE path/to/STM32Cube_FW/Drivers/STM32xxxx_HAL_Driver/Inc)
target_link_libraries(STM32Cube_Project path/to/STM32Cube_FW/Drivers/STM32xxxx_HAL_Driver/Src)

# CMake for Bare Metal Programming
add_executable(BareMetal_Project ${COMMON_SOURCES})

# CMake for Mbed OS
find_package(MbedOS COMPONENTS REQUIRED)
add_executable(MbedOS_Project ${COMMON_SOURCES})
target_link_libraries(MbedOS_Project MbedOS::MbedOS)

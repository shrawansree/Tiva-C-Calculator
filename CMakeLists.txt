cmake_minimum_required(VERSION 3.24)
project(Mini_Project C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(RTE)
include_directories(RTE/_Target_1)
include_directories(RTE/Device/TM4C123GH6PM)


add_executable(Mini_Project
        RTE/_Target_1/RTE_Components.h
        RTE/Device/TM4C123GH6PM/system_TM4C123.c
        Calculator.c
        Keypad.c
        LCD.c
        main.c
        PLL.c
        UART.c
        UART.h Graphics.c Graphics.h Graphics.h Calculator.h LCD.h PLL.h Keypad.h Password.c Password.h)

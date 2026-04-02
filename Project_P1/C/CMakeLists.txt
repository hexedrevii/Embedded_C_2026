cmake_minimum_required(VERSION 3.12)

project("Embedded_C_2026" LANGUAGES C)

add_executable(${PROJECT_NAME}
    sw/main.c
    sw/DataTypes/inc/Types.h
    sw/FlowControl/inc/Fcontrol.h
    sw/FlowControl/inc/Messages.h
    sw/FlowControl/src/Fcontrol.c
    sw/FlowControl/src/MessagesGen.c
)

target_include_directories(${PROJECT_NAME} PRIVATE
    sw/DataTypes/inc
    sw/FlowControl/inc
)
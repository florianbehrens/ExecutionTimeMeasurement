project(ExecutionTimeMeasurement)
cmake_minimum_required(VERSION 2.8)
add_definitions(-std=c++0x)

add_library(
    ${PROJECT_NAME}
    measurement.cpp
    measurement.h
)
add_executable(
    ${PROJECT_NAME}Test
    main.cpp
)
target_link_libraries(
    ${PROJECT_NAME}Test
    ${PROJECT_NAME}
    pthread
)

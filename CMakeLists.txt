project(ExecutionTimeMeasurement)
cmake_minimum_required(VERSION 2.8)
add_definitions(-std=c++0x)
add_executable(
    ${PROJECT_NAME}
    main.cpp
    measurement.cpp
    measurement.h
)
target_link_libraries(
    ${PROJECT_NAME}
    pthread
)

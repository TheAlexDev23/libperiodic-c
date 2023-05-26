cmake_minimum_required(VERSION 3.18.0)

project(periodic-c)

add_library(
    ${PROJECT_NAME}
    periodic.h
    periodic.c
    element.h
    element.c
)

target_link_libraries(${PROJECT_NAME} json-c)
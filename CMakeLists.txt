cmake_minimum_required(VERSION 3.14.5)
project(andronaut)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/ANUT")

file(GLOB SRC_FILES
    "${SRC_DIR}/*.cpp"
    "${SRC_DIR}/graphics/*.cpp"
    "${SRC_DIR}/math/*.cpp"
    "${SRC_DIR}/utils/*.cpp"
)

add_library(andronaut OBJECT 
    "${SRC_FILES}"
    "${CMAKE_CURRENT_SOURCE_DIR}/glue/android_native_app_glue.c"
)

set_property(TARGET andronaut PROPERTY POSITION_INDEPENDENT_CODE ON)
target_link_libraries(andronaut PUBLIC GLESv3 EGL android)

target_include_directories(andronaut PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/"
    "${CMAKE_CURRENT_SOURCE_DIR}/glue/"
)

cmake_minimum_required(VERSION 3.14.5)
project(andronaut)

file(GLOB SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/math/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/utils/*.cpp"
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

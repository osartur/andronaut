cmake_minimum_required(VERSION 3.14.5)
project(andronaut)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB SRC_FILES
    "${SRC_DIR}/system/*.cpp"
    "${SRC_DIR}/vendor/*.cpp"
    "${SRC_DIR}/graphics/gles/*.cpp"
)

add_library(andronaut OBJECT "${SRC_FILES}")
set_property(TARGET andronaut PROPERTY POSITION_INDEPENDENT_CODE ON)
target_link_libraries(andronaut PUBLIC GLESv3 EGL android)

target_include_directories(andronaut PRIVATE 
    "${SRC_DIR}/"
)

target_include_directories(andronaut INTERFACE
    "${SRC_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/"
)


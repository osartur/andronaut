cmake_minimum_required(VERSION 3.14.5)
project(andronaut)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/andronaut/src")

file(GLOB SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/andronaut/vendor/*.cpp"
    "${SRC_DIR}/*.cpp"
    "${SRC_DIR}/graphics/*.cpp"
    "${SRC_DIR}/utils/*.cpp"
)

add_library(andronaut OBJECT "${SRC_FILES}")

set_property(TARGET andronaut PROPERTY POSITION_INDEPENDENT_CODE ON)
target_link_libraries(andronaut PUBLIC GLESv3 EGL android)

target_include_directories(andronaut PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/andronaut/"
    "${CMAKE_CURRENT_SOURCE_DIR}/andronaut/src/"
)

target_include_directories(andronaut INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/"
)


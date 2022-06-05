cmake_minimum_required(VERSION 3.12)
project(OpenGLRubiksCube)
set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 REQUIRED)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SHADER_DIR ${CMAKE_SOURCE_DIR}/shader)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

file(
    GLOB SOURCES
    ${INCLUDE_DIR}/*.h
    ${SHADER_DIR}/*.glsl
    ${SOURCE_DIR}/*.c
    ${SOURCE_DIR}/*.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${INCLUDE_DIR}
)

target_link_libraries(
    ${PROJECT_NAME}
    glfw
)
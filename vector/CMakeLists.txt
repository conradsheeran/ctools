cmake_minimum_required(VERSION 3.10.0)
project(vector VERSION 0.1.0 LANGUAGES C)

add_executable(vector
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/vector.c
)

target_include_directories(vector PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(convex-hull-example)

add_executable(convex_hull convex_hull.cpp)
target_link_libraries(convex_hull visualization ${GMP_LIBRARIES})


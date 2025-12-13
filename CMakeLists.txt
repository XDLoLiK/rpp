cmake_minimum_required(VERSION 3.14)

project(RPP LANGUAGES CXX)

add_executable(rpp)

target_sources(rpp
  PRIVATE
    src/main.cpp
    src/rpp.cpp
    src/algo/dfs.cpp
    src/algo/connected_components.cpp
    src/algo/floyd_warshall.cpp
    src/algo/hungarian.cpp
)

cmake_minimum_required(VERSION 3.22)
project(HelloWorld)
find_package(Kokkos REQUIRED)

add_executable(HelloWorld hello_world.cpp)
target_link_libraries(HelloWorld Kokkos::kokkos)

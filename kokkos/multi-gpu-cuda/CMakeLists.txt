cmake_minimum_required(VERSION 3.22)
project(MultiGpuCuda)
find_package(Kokkos REQUIRED)

add_executable(MultiGpuCuda multi_gpu_cuda.cpp)
target_link_libraries(MultiGpuCuda Kokkos::kokkos)

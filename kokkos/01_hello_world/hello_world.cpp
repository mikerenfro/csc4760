// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright Contributors to the Kokkos project

#include <Kokkos_Core.hpp>
#include <cstdio>
struct hello_world {
  KOKKOS_INLINE_FUNCTION
  void operator()(const int i) const {
    Kokkos::printf("Hello from i = %i\n", i);
  }
};

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  printf("Hello World on Kokkos execution space %s\n",
         Kokkos::DefaultExecutionSpace::name());
  Kokkos::parallel_for("HelloWorld", 15, hello_world());
  Kokkos::finalize();
}

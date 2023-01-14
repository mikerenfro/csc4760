#include <iostream>
#include <omp.h>

int main(int argc, char** argv){
    #pragma omp parallel
    {
        std::cout << "Hello from process: " << omp_get_thread_num() << std::endl;
    }
    return 0;
}
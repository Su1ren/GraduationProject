#include <iostream>
#include "benchmark.h"

int main(int argc,char *argv[]) {
    std::cout << "Loading..." << '\n';
    /* for(uint32_t i = 1;i < argc;++i) {
        std::cout << argv[i] << std::endl;
        BenchMark dataset(argv[i]);
        dataset.TopKError(0.0001);
    } */
    //std::cout << "HyperGSU" << '\n';
    BenchMark dataset("Dataset/SYN20.dat");
    dataset.TopKError(0.00001);
    return 0;
}
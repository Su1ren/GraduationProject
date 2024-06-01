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
    BenchMark dataset("Dataset/u32.dat");
    dataset.TopKError(0.00002);
    return 0;
}
#include <iostream>
#include "rangeAllocator.h"
#include "tests.hpp"

#define __DEBUG__MAIN
//#define SIZE        (1024*1024UL)
#define SIZE  (1024L)
#define RANGE_SIZE  (1024L)

int main(int argc, const char * argv[]) {

    // create a range
    // malloc SIZE byte of memory usins malloc
    void *p = malloc(SIZE);
#ifdef __DEBUG__MAIN
    std::cout << "Malloc'ed " << SIZE << " bytes" << std::endl;
#endif
    RangeAllocator ra((vaddr_t)p, RANGE_SIZE, 8);
    ra.printFreeList();
    runTests(ra);
    ra.printFreeList();
    return 0;
}

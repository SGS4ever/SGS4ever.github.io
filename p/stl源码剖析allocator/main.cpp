#include <memory>
#include <chrono>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>


int main()
{
    std::ifstream fin("./MemAllocSeq");
    std::vector<size_t> memAllocSeq;
    size_t i;
    while (fin >> i) {
        memAllocSeq.push_back(i);
    }

    std::allocator<uint8_t> alloc;
    auto start = std::chrono::steady_clock::now();
    std::for_each(memAllocSeq.begin(), memAllocSeq.end(), [&alloc](size_t size) {
        auto mem = alloc.allocate(size);
        alloc.deallocate(mem, size);
    });
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double, std::milli> ms = end - start;
    std::cout << "Toal cost: " << ms.count() << " ms\n";

    return 0;
}

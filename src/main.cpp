#include "dmultimap.hpp"
#include <cstdint>
#include <random>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "usage " << argv[0] << " [output_file] [record_count]" << std::endl;
        return 1;
    }
    std::string tmpfile(argv[1]);
    uint64_t count = std::stoll(argv[2]);
    dmultimap::dmultimap<uint64_t, uint64_t> map(tmpfile);
    unsigned seed =  std::chrono::system_clock::to_time_t(std::chrono::high_resolution_clock::now());
    std::minstd_rand0 generator(seed);
    uint64_t m = 0;
    for (uint64_t i = 0; i < count; ++i) {
        uint64_t j = (generator() % count)/2;
        map.append(j, j*2);
        m = std::max(j, m);
    }
    map.index(m);
    map.for_each_pair([&](uint64_t a, uint64_t b) {
            assert(a*2 == b);
        });
    return 0;
}

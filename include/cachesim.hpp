#pragma once

#include <fstream>
#include <tuple>
#include <vector>

class CacheSim
{   
    std::ifstream infile;

    // cache settings
    unsigned int block_size;
    unsigned int associativity;
    unsigned int capacity;
    unsigned int miss_penalty;
    unsigned int dirty_wb_penalty;

    // access settings
    unsigned int set_offset;
    unsigned int tag_offset;
    unsigned int set_mask;

    // cache state
    std::vector<std::uint64_t> tags;
    std::vector<char> dirty; // почему не bool?
    std::vector<char> valid; // почему не bool?
    std::vector<int> priority;

public:
    CacheSim(
        std::string input, 
        unsigned int bs, 
        unsigned int a,
        unsigned int c,
        unsigned int mp,
        unsigned int wbp
    );
    ~CacheSim();

    void run();
    std::tuple<bool, std::uint64_t, int> parse_line(std::string access);
};
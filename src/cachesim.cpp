#include "include/cachesim.hpp"
#include <string>
#include <bit>

CacheSim::CacheSim(std::string input, unsigned int bs, 
        unsigned int a,
        unsigned int c,
        unsigned int mp,
        unsigned int wbp)
{
    infile.open(input);

    // set cache settings
    block_size = bs;
    associativity = a;
    capacity = c;
    miss_penalty = mp;
    dirty_wb_penalty = wbp;

    // reshape our cache state
    unsigned int num_blocks = capacity / block_size;

    tags.resize(num_blocks);
    dirty.resize(num_blocks);
    valid.resize(num_blocks);
    priority.resize(num_blocks);

    // set address mask and offsets
    // Cache lines come in the following format:
    // |****** TAG ******|**** SET ****|** OFFSET **|
    auto block_bits = std::popcount(block_size - 1);
    set_offset = block_bits;

    auto sets = capacity / (block_size * associativity);
    set_mask = sets - 1;

    auto set_bits = std::popcount(set_mask);

    tag_offset = block_bits + set_bits;


}

CacheSim::~CacheSim()
{
    infile.close();
}

void CacheSim::run()
{
    std::string line;
    while (std::getline(infile, line))
    {
        // parse and read
        auto [type, address, instructions] = parse_line(line);
    }
}

std::tuple<bool, std::uint64_t, int> CacheSim::parse_line(std::string access)
{
    int type;
    std::uint64_t address;
    int instructions_count;

    sscanf(access.c_str(), "# %d %lx %d", &type, &address, &instructions_count);
    return {type, address, instructions_count};
}
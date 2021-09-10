#pragma once
#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <random>
#include <stdexcept>
#include <utility>


namespace cuckoo
{
    /**
    The type that represents a 128-bit item that can be added to the hash table.
    */
    //using item_type = std::string;
    using item_type = std::pair<unsigned long, std::string>;

    /**
    The type that represents a location in the hash table.
    */
    using location_type = std::uint32_t;

    /**
    The type that represents the size of a hash table.
    */
    using table_size_type = location_type;


    /**
    The smallest allowed table size.
    */
    constexpr table_size_type min_table_size = table_size_type(1);

    /**
    The largest allowed table size.
    */
    constexpr table_size_type max_table_size = table_size_type(1) << 30;




    /**
    Returns whether two hash table items are equal.

    @param[in] in1 The first hash table item
    @param[in] in2 The second hash table item
    */
    inline bool are_equal_item(const item_type& in1, const item_type& in2) noexcept
    {
        //return (get_low_word(in1) == get_low_word(in2)) && (get_high_word(in1) == get_high_word(in2));
        return (in1.first == in2.first && (in1.second.compare(in2.second) == 0));
        //return (in1.first == in2.first);
    }


}
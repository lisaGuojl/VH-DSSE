#pragma once
#pragma once
//
// Created by shangqi on 2020/6/17.
//

#ifndef CUCKOO_H
#define CUCKOO_H
#include <iostream>
#include <bitset>
#include <vector>
#include <random>



#include "GGMTree.h"
#include "common.h"
#include "Utils.h"

using namespace std;

namespace cuckoo {
    class KukuTable {
    private:
        /*The hash table that holds all of the input data.*/
        std::vector<item_type> table_;

        /*The stash.*/
        std::vector<item_type> stash_;

        /*
        Seed for the hash functions
        */
        const item_type loc_func_seed_;

        /*
        The maximum number of attempts that are made to insert an item.
        */
        const std::uint64_t max_probe_;

        /*
        An item value that denotes an empty item.
        */
        const item_type empty_item_;

        /*
        The size of the table.
        */
        const table_size_type table_size_;

        /*
        The size of the stash.
        */
        const table_size_type stash_size_;

        // PRF
        std::uint8_t* prf_seed_;
        GGMTree* tree;


        inline item_type swap(item_type item, location_type location) noexcept
        {
            item_type old_item = table_[location];
            table_[location] = item;
            return old_item;
        }

        /*
        Randomness source for location function sampling.
        */
        std::random_device rd;
        //std::mt19937_64 gen(rd());
        inline int generate_random_bit() noexcept {
            std::mt19937_64 gen(rd());
            std::bernoulli_distribution d(0.5);
            return (int) d(gen);
        }
        

    public:
        KukuTable(
            table_size_type table_size, table_size_type stash_size, std::uint64_t max_probe, item_type empty_item, std::uint8_t* prf_seed);

        /**
        Clears the hash table by filling every location with the empty item.
        */
        void clear_table();

        void insert_by_loc(location_type location, string value);
        bool insert(unsigned long index, string value);

        item_type get_loc(location_type location);
        item_type get(unsigned long index);


        inline table_size_type table_size() const noexcept
        {
            return table_size_;
        }

        /**
        Returns a reference to the hash table.
        */
        inline const std::vector<item_type>& table() const noexcept
        {
            return table_;
        }

        /**
        Returns a reference to a specific location in the hash table.

        @param[in] index The index in the hash table
        @throws std::out_of_range if index is out of range
        */
        inline const item_type& table(location_type index) const
        {
            if (index >= table_size_)
            {
                throw std::out_of_range("index is out of range");
            }
            return table_[index];
        }

        /**
        Returns a reference to the stash.
        */
        inline const std::vector<item_type>& stash() const noexcept
        {
            return stash_;
        }

        /**
        Returns a reference to a specific location in the stash.

        @param[in] index The index in the stash
        @throws std::out_of_range if index is out of range
        */
        inline const item_type& stash(location_type index) const
        {
            if (index >= stash_size_)
            {
                throw std::out_of_range("index is out of range");
            }
            if (index >= stash_.size() && index < stash_size_)
            {
                return empty_item_;
            }
            return stash_[index];
        }

        inline bool is_empty(location_type index) const noexcept
        {
            return is_empty_item(table(index));
        }

        /**
        Returns whether a given item is the empty item for this hash table.

        @param[in] item The item to compare to the empty item
        */
        inline bool is_empty_item(const item_type& item) const noexcept
        {
            return are_equal_item(item, empty_item_);
        }

        //std::string uint82hex(const uint8_t* data, int data_length) const {
        //    std::stringstream ss;
        //    ss << std::hex << std::setfill('0');
        //    for (int i = 0; i < data_length; ++i)
        //        ss << std::setw(2) << static_cast<unsigned>(data[i]);
        //    std::string mystr = ss.str();
        //    return mystr;
        //}



        inline location_type location(unsigned long index, int prf_ind) const
        {
            if (prf_ind == 1)
            {
                index = index + 1;
            }
            uint8_t derived_key[16];
            memcpy(derived_key, prf_seed_, 16);
            GGMTree::derive_key_from_tree(derived_key, index, tree->get_level(), 0);
            location_type loc;
            
            while (true) {
                uint32_t loc32 = derived_key[0] | (derived_key[1] << 8) | (derived_key[2] << 16) | (derived_key[3] << 24);
                int length = ceil(log2(table_size_));
                loc = (uint32_t)(loc32 & ((length == 32) ? 0xFFFFFFFF : (((uint32_t)1 << length) - 1)));
                if (loc < table_size_) {
                    return loc;
                }
                else {
                    uint8_t digest[32] = {};
                    sha256_digest(derived_key, 32, digest);
                    memcpy(derived_key, digest, 16);
                }
            }
            /*for (int i = 0; i < 4; i++) {
                uint32_t loc32 = derived_key[4*i] | (derived_key[4 * i+1] << 8) | (derived_key[4 * i+2] << 16) | (derived_key[4 * i+3] << 24);
                int length = ceil(log2(table_size_));
                loc = (uint32_t)(loc32 & ((length == 32) ? 0xFFFFFFFF : (((uint32_t)1 << length) - 1)));
                if (loc < table_size_) {
                    return loc;
                }
            }*/
           
            //loc = table_size_;
            //return loc;
        }

    };

}




#endif //CUCKOO_H

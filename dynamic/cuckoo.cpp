#include "cuckoo.h"

using namespace std;

namespace cuckoo
{

    KukuTable::KukuTable(
        table_size_type table_size, table_size_type stash_size, std::uint64_t max_probe, item_type empty_item, std::uint8_t* prf_seed)
        : table_size_(table_size), stash_size_(stash_size), max_probe_(max_probe), empty_item_(empty_item), prf_seed_(prf_seed)
    {
        if (table_size < min_table_size || table_size > max_table_size)
        {
            throw invalid_argument("table_size is out of range");
        }
        // Allocate the hash table
        table_.resize(table_size_, empty_item_);

        tree = new GGMTree(GGM_SIZE);

    }

    void KukuTable::clear_table()
    {
        size_t sz = table_.size();
        table_.resize(0);
        table_.resize(sz, empty_item_);
        //table_.clear();
        stash_.clear();
    }

    void KukuTable::insert_by_loc(location_type loc, string str)
    {
        item_type item = make_pair(loc, str);
        table_[loc] = item;
    }

    bool KukuTable::insert(unsigned long ind, string str)
    {
        item_type item;
        item = std::make_pair(ind, str);
        uint64_t level = max_probe_;
        while (level--)
        { 
            unsigned long index = item.first;
            for (int i = 0; i < 2; ++i) {
                location_type loc = location(index, i);
                if (loc == table_size_) {
                    return false;
                }
                if (is_empty_item(table_[loc])) {
                    /*std::cout << loc << endl;*/
                    table_[loc] = item;
                    return true;
                }
            }
            
            int prf_ind = generate_random_bit();
            item = swap(item, location(index, prf_ind));

        }
        return false;
        /*if (stash_.size() < stash_size_)
            {
                stash_.push_back(item);
                return true;
            }
            else
            {
                return false;
            }*/
        
    }

    item_type KukuTable::get_loc(location_type location)
    {
        int length = ceil(log2(table_size_));
        location_type loc = (uint32_t)(location & ((length == 32) ? 0xFFFFFFFF : (((uint32_t)1 << length) - 1)));

        item_type item;
        item = table_[loc];
        return item;
    }

    item_type KukuTable::get(unsigned long index)
    {
        location_type location32 = location(index, 0);
        int length = ceil(log2(table_size_));
        location_type loc = (uint32_t)(location32 & ((length == 32) ? 0xFFFFFFFF : (((uint32_t)1 << length) - 1)));

        item_type item;
        item = table_[loc];
        return item;
    }

}

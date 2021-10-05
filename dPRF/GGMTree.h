#pragma once
#ifndef DELEGATABLE_PRF_GGMTREE_H
#define DELEGATABLE_PRF_GGMTREE_H

#include <bitset>
#include <cmath>
#include <cstring>
#include <vector>

#include "GGMNode.h"
#include "Utils.h"


using namespace std;

class GGMTree {
private:
    int level;

public:
    explicit GGMTree(long long num_node);
    void static derive_key_from_tree(uint8_t* current_key, long offset, unsigned int start_level, unsigned int target_level);
    void static get_leaf_node(uint8_t* current_key, bool ind, unsigned int start_level);
    vector<GGMNode> min_coverage(vector<GGMNode> node_list);
    int get_level() const;
};


#endif

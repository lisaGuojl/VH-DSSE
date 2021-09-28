#include "GGMTree.h"
GGMTree::GGMTree(long long num_node) {
    this->level = ceil(log2(num_node));
}

void GGMTree::derive_key_from_tree(uint8_t* current_key, long offset, unsigned int start_level, unsigned int target_level) {
    uint8_t next_key[AES_BLOCK_SIZE];
    // does not need to derive
    if (start_level == target_level) return;
    // derive tag
    for (unsigned int k = start_level; k > target_level; --k) {
        int k_bit = (offset & (1 << (k - 1))) >> (k - 1);
        uint8_t digest[32] = {};
        sha256_digest(current_key, AES_BLOCK_SIZE, digest);
        if (k_bit == 0) {
            memcpy(next_key, digest+sizeof(uint8_t)*16, AES_BLOCK_SIZE);
        }
        else {
            memcpy(next_key, digest, AES_BLOCK_SIZE);
        }
        memcpy(current_key, next_key, AES_BLOCK_SIZE);
    }
}

vector<GGMNode> GGMTree::min_coverage(vector<GGMNode> node_list) {
    vector<GGMNode> next_level_node;

    for (int i = 0; i < node_list.size(); ++i) {
        auto node1 = node_list[i];

        if (i + 1 == node_list.size()) {
            next_level_node.emplace_back(node1);
        }
        else {
            auto node2 = node_list[i + 1];
            // same parent in the binary path
            if (((node1.index >> 1) == (node2.index >> 1)) && (node1.level == node2.level)) {
                next_level_node.emplace_back(GGMNode(node1.index >> 1, node1.level + 1));
                i++;
            }
            else {
                next_level_node.emplace_back(node1);
            }
        }
    }

    // no merge return
    if (next_level_node.size() == node_list.size() || next_level_node.empty()) {
        return node_list;
    }

    return min_coverage(next_level_node);
}

int GGMTree::get_level() const {
    return level;
}
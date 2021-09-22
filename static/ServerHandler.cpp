
#include "ServerHandler.h"

ServerHandler::ServerHandler(uint32_t table_size) {
    edb_size = table_size;
    /*item_type empty_item = make_pair((unsigned long)-1, "NULL");
    uint8_t* prf_seed = (unsigned char*)"0123456789123456";
    table = new KukuTable(table_size, 0, 0, empty_item, prf_seed);*/
}

ServerHandler::~ServerHandler() {
    //table->clear_table();
    edb.clear();
    estash.clear();
    buffer.clear();
}

void ServerHandler::addEDB(const std::vector<string>& client_edb, const std::vector<string>& stash) {
    edb.reserve(edb_size);
    for (auto i : client_edb) {
        edb.emplace_back(i);
    }
    estash.clear();
    for (auto i : stash) {
        estash.emplace_back(i);
    }
}


vector<string> ServerHandler::search(const vector<GGMNode>& node_list) {

    vector<string> results;

    for (GGMNode n : node_list) {
        std::queue<GGMNode> internal_nodes;
        internal_nodes.push(n);
        int level = n.level;
        while (level > 0) {
            GGMNode node = internal_nodes.front();

            internal_nodes.pop();
            uint8_t derived_key[16];
            memcpy(derived_key, node.digest, 16);
            GGMTree::derive_key_from_tree(derived_key, node.index, node.level, node.level - 1);
            internal_nodes.push(GGMNode(node.index, node.level - 1, derived_key));

            memcpy(derived_key, node.digest, 16);
            GGMTree::derive_key_from_tree(derived_key, node.index + pow(2, node.level - 1), node.level, node.level - 1);
            internal_nodes.push(GGMNode(node.index + pow(2, node.level - 1), node.level - 1, derived_key));
            level = internal_nodes.front().level;
        }
        while (internal_nodes.empty()) {
            GGMNode node = internal_nodes.front();
            internal_nodes.pop();
            while (true) {
                uint32_t loc32 = node.digest[0] | (node.digest[1] << 8) | (node.digest[2] << 16) | (node.digest[3] << 24);
                int length = ceil(log2(edb.size()));
                uint32_t loc = (uint32_t)(loc32 & ((length == 32) ? 0xFFFFFFFF : (((uint32_t)1 << length) - 1)));
                if (loc < edb.size()) {
                    results.emplace_back(edb[loc]);
                    break;
                }
                else {
                    uint8_t digest[32] = {};
                    sha256_digest(node.digest, 16, digest);
                    memcpy(node.digest, digest, 16);
                }
            }
        }

    }


    return results;
}
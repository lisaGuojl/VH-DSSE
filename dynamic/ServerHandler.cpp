
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
    for (GGMNode node : node_list) {
        for (int i = 0; i < pow(2, node.level); ++i) {
            int offset = (node.index) + i;
            uint8_t derived_key[16];
            memcpy(derived_key, node.digest, 16);
            GGMTree::derive_key_from_tree(derived_key, offset, node.level, 0);
            while (true) {
                uint32_t loc32 = derived_key[0] | (derived_key[1] << 8) | (derived_key[2] << 16) | (derived_key[3] << 24);
                int length = ceil(log2(edb_size));
                uint32_t loc = (uint32_t)(loc32 & ((length == 32) ? 0xFFFFFFFF : (((uint32_t)1 << length) - 1)));
                if (loc < edb_size) {
                    results.emplace_back(edb[loc]);
                    break;
                }
                else {
                    uint8_t digest[32] = {};
                    sha256_digest(derived_key, 16, digest);
                    memcpy(derived_key, digest, 16);
                }
            }
            /*for (int i = 0; i < 4; i++) {
                uint32_t loc32 = derived_key[4 * i] | (derived_key[4 * i + 1] << 8) | (derived_key[4 * i + 2] << 16) | (derived_key[4 * i + 3] << 24);
                int length = ceil(log2(edb_size));
                loc = (uint32_t)(loc32 & ((length == 32) ? 0xFFFFFFFF : (((uint32_t)1 << length) - 1)));
                if (loc < edb_size) {
                    results.emplace_back(edb[loc]);
                    break;
                }
            }*/
            
        }
    }
    for (auto j : estash) {
        results.emplace_back(j);
    }
    return results;
}

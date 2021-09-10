#include "Server.h"

Server::Server() {

}

Server::~Server() {
    //table->clear_table();
    EDBs.clear();
    estash.clear();
    buffer.clear();
}

void Server::addEDB(const unordered_map<int, vector<string>>& client_edbs, const std::vector<string>& stash, const std::vector<string>& client_buffer) {
    EDBs.clear();
    EDBs = client_edbs;
    
    estash.clear();
    for (auto i : stash) {
        estash.emplace_back(i);
    }

    buffer.clear();
    buffer = client_buffer;
}

void Server::add_entries(const std::vector<string>& ciphertext) {
    for (auto i : ciphertext) {
        buffer.emplace_back(i);
    }
}

vector<string> Server::searchEDB(int id, const vector<GGMNode>& node_list) {
    vector<string> edb = {};
    edb = EDBs[id];
    vector<string> results;
    for (GGMNode node : node_list) {
        cout<< "try"<<endl;
        for (int i = 0; i < pow(2, node.level); ++i) {
            int offset = (node.index) + i;
            uint8_t derived_key[16];
            memcpy(derived_key, node.digest, 16);
            GGMTree::derive_key_from_tree(derived_key, offset, node.level, 0);
            while (true) {
                uint32_t loc32 = derived_key[0] | (derived_key[1] << 8) | (derived_key[2] << 16) | (derived_key[3] << 24);
                int length = ceil(log2(edb.size()));
                uint32_t loc = (uint32_t)(loc32 & ((length == 32) ? 0xFFFFFFFF : (((uint32_t)1 << length) - 1)));
                if (loc < edb.size()) {
                    results.emplace_back(edb[loc]);
                    break;
                }
                else {
                    uint8_t digest[32] = {};
                    sha256_digest(derived_key, 16, digest);
                    memcpy(derived_key, digest, 16);
                }
            }

        }
    }
    return results;
}

vector<string> Server::searchEstash() {
    return estash;
}

vector<string> Server::searchBuffer() {
    return buffer;
}

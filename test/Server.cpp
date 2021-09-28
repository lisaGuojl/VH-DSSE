#include "Server.h"

Server::Server() {

}

Server::~Server() {
    //table->clear_table();
    EDBs.clear();
    estash.clear();
    buffer.clear();
}

void Server::storeEDB(const vector<pair<int, vector<string>>>& client_edbs, const std::vector<string>& stash, const std::vector<string>& client_buffer, int min_value, int logN) {
    EDBs.clear();
    EDBs.resize(logN+1);
    min = min_value;
    for (auto pair : client_edbs) {
        EDBs[pair.first].assign(pair.second.begin(), pair.second.end());
    }
   

    estash.clear();
    for (auto i : stash) {
        estash.emplace_back(i);
    }

    buffer.clear();
    buffer = client_buffer;
}


vector<string> Server::searchEDB(int id, const vector<GGMNode>& node_list) {
    vector<string>* edb;
    edb = &EDBs[id];
    //edb.assign(EDBs[id].begin(), EDBs[id].end());
    vector<string> results;
    
    for (GGMNode node : node_list) {
        time_start = chrono::high_resolution_clock::now();
        for (int i = 0; i < pow(2, node.level); ++i) {
            int offset = (node.index) + i;
            uint8_t derived_key[16];
            memcpy(derived_key, node.digest, 16);
            GGMTree::derive_key_from_tree(derived_key, offset, node.level, 0);
            
            for (int j=0; j<50; j++) {
                uint32_t loc32 = derived_key[0] | (derived_key[1] << 8) | (derived_key[2] << 16) | (derived_key[3] << 24);
                int length = ceil(log2(edb->size()));
                uint32_t loc = (uint32_t)(loc32 & ((length == 32) ? 0xFFFFFFFF : (((uint32_t)1 << length) - 1)));
                if (loc < edb->size()) {
                    results.emplace_back(edb->at(loc));
                    break;
                }
                else {
                    uint8_t digest[32] = {};
                    sha256_digest(derived_key, 16, digest);
                    memcpy(derived_key, digest, 16);
                }
            }

        }
        time_end = chrono::high_resolution_clock::now();
	      time_diff = chrono::duration_cast<chrono::microseconds>(time_end - time_start);
        cout << "2:"<< time_diff.count() << " microseconds]" << endl;
    }
    return results;
}

vector<string> Server::searchEstash() {
    return estash;
}

vector<string> Server::searchBuffer() {
    return buffer;
}


bool Server::update(string ct) {
    buffer.emplace_back(ct);
    if (buffer.size() == (int)(1 << (min + 1))) {
        return false;
    }
    return true;
    
}

vector<pair<int, vector<string>>> Server::updateDB() {
    int i = min;
    vector<pair<int, vector<string>>> res;
    while (true) {
        if (EDBs.empty() != 1 && EDBs[i].size() != 0) {
            res.emplace_back(make_pair(i, EDBs[i]));
            EDBs[i] = {};
            i++;
        }
        else {
            break;
        }
    }
    return res;
}


void Server::storeEDB(int ind, vector<string>& EDB, vector<string>& stash) {
    buffer.clear();
    estash.clear();
    for (auto i : stash) {
        estash.emplace_back(i);
    }
    vector<string> edb = {};
    for (auto i : EDB) {
        edb.emplace_back(i);
    }
    EDBs[ind] = edb;
    min = ind;
}

int Server::getStashSize() {
    return (int)estash.size();
}

int Server::getBufferSize() {
    return (int)buffer.size();
}

int Server::getEDBSize(int i) {
    return (int)EDBs[i].size();
}

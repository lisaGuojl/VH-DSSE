#pragma once
#pragma once


#ifndef SERVER_H
#define SERVER_H


#include <chrono>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>

#include "Utils.h"

#include "GGMTree.h"
#include "cuckoo.h"


using namespace std;
using namespace cuckoo;

class Server {
private:
    vector<string> buffer;
    unordered_map<int, vector<string>> EDBs;
    vector<string> estash;
    uint32_t edb_size;



public:
    Server();
    ~Server();
    void add_entries(const std::vector<string>& ciphertext);
    void addEDB(const unordered_map<int, vector<string>>& client_edbs, const std::vector<string>& stash, const std::vector<string>& buffer);
    vector<string> searchEDB(int id, const vector<GGMNode>& node_list);
    vector<string> searchEstash();
    vector<string> searchBuffer();
};


#endif //SERVER\_H
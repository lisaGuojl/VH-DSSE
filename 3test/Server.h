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
    int min;



public:
    Server();
    ~Server();

    void storeEDB(const unordered_map<int, vector<string>>& client_edbs, const std::vector<string>& stash, const std::vector<string>& buffer, int min_value);
    vector<string> searchEDB(int id, const vector<GGMNode>& node_list);
    vector<string> searchEstash();
    vector<string> searchBuffer();

    bool update(string ct);
    vector<pair<int, vector<string>>> updateDB();
    void storeEDB(int ind, vector<string>& EDB, vector<string>& stash);
    
    int getStashSize();
    int getBufferSize();
    int getEDBSize(int i);
};


#endif //SERVER\_H

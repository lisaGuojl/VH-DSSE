#pragma once


#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H


#include <chrono>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <queue>
#include "Utils.h"

#include "GGMTree.h"
#include "cuckoo.h"

//using namespace chrono;
using namespace std;
using namespace cuckoo;

class ServerHandler {
private:
    vector<string> buffer;
    vector<string> edb;
    vector<string> estash;
    uint32_t edb_size;

    //KukuTable* table;

public:
    ServerHandler(uint32_t table_size);
    ~ServerHandler();
    //void add_entries(const string& ciphertext);
    void addEDB(const std::vector<string>& client_edb, const std::vector<string>& stash);
    vector<string> search(const vector<GGMNode>& node_list);
};


#endif //SERVERHANDLER_H
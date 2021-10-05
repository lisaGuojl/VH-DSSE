#pragma once
#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#include <vector>
#include <queue>
#include "Utils.h"

#include "GGMTree.h"
#include "cuckoo.h"

using namespace std;
using namespace cuckoo;

class ServerHandler {
private:
    vector<string> buffer;
    vector<string> edb;
    vector<string> estash;
    uint32_t edb_size;

public:
    ServerHandler(uint32_t table_size);
    ~ServerHandler();
    void addEDB(const std::vector<string>& client_edb, const std::vector<string>& stash);
    vector<string> search(const vector<GGMNode>& node_list);
};


#endif //SERVERHANDLER_H
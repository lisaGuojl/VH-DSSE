#pragma once


#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <functional>
#include <unordered_map>
#include "GGMTree.h"
#include "cuckoo.h"

#include "ServerHandler.h"

#ifdef _WIN32
#define stringcpy(destination, length, source) strcpy_s(destination, length, source)
#else
#define stringcpy(destination, length, source) strncpy(destination, source, length)
#endif


using namespace cuckoo;



enum OP {
    ADD, DEL
};

struct kv {
    string keyword;
    int ind;
    OP op;
    string text;
};

class ClientHandler {
private:
    uint8_t* key = (unsigned char*)"01234567891234560123456789123456";
    uint8_t* iv = (unsigned char*)"01234567891234560123456789123456";
    uint8_t* prf_seed = (unsigned char*)"01234567891234560123456789123456";
    float alpha;

    GGMTree* tree;
    KukuTable* table;
    std::vector<string> stash;
    std::vector<string> edb;
    int table_size;
    int stash_len;
  

    ServerHandler* server;


public:
    ClientHandler(int size, float alpha);
    ~ClientHandler();
    unsigned long get_index(const string& keyword, unsigned short ind);
    void shuffleDB(vector<kv>* db);
    void update(const string& keyword, int ind, OP op, string& text);
    void upload();
    int setup(vector<kv> db);
    vector<GGMNode> getToken(const string& keyword, int length);
    vector<string> search(const string& keyword, int length);
};


#endif //CLIENTHANDLER_H

#pragma once


#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H


#include <functional>
#include <string>
#include "GGMTree.h"
#include "cuckoo.h"
#include "ServerHandler.h"
using namespace std;
#ifdef _WIN32
#define stringcpy(destination, length, source) strcpy_s(destination, length, source)
#else
#define stringcpy(destination, length, source) strncpy(destination, source, length)
#endif

using namespace cuckoo;

enum OP {
    INS, DEL
};

struct kv {
    string keyword;
    int ind;
    string text;
};

class ClientHandler {
private:
    uint8_t* key = (unsigned char*)"7891234560123456";
    uint8_t* iv = (unsigned char*)"0123456789123456";
    uint8_t* prf_seed = (unsigned char*)"0123456789123456";


    GGMTree* tree;
    KukuTable* table;
    std::vector<string> stash;
    std::vector<string> edb;
    uint32_t table_size;

    //unsigned long get_index(const string& keyword, unsigned short ind);

public:
    ClientHandler(int size, float alpha, string& seedstr);
    ~ClientHandler();
    int stash_len;
    unsigned long get_index(const string& keyword, unsigned short ind);
    int setup(vector<kv> db);
    vector<string> get_edb();
    vector<string> get_estash();
    void update(const string& keyword, int ind, string& text);
    void upload();
    vector<GGMNode> getToken(const string& keyword, int length, uint8_t* prf_seed);
    int addEDB(vector<string> plains);
};


#endif //CLIENTHANDLER_H

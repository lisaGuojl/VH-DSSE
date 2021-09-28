#pragma once
#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <functional>
#include <string>
#include <unordered_map>
#include "GGMTree.h"
#include "cuckoo.h"
#include "Utils.h"
using namespace std;
using namespace cuckoo;
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
    uint8_t* Kstash = (unsigned char*)"7891234560123456"; 
    uint8_t* Kske = (unsigned char*)"7891234560123456";
    uint8_t* iv = (unsigned char*)"0123456789123456";
    uint8_t* prf_seed = (unsigned char*)"0123456789123456";

    float alpha;
    GGMTree* tree;
    KukuTable* table;
    std::vector<string> stash;
    std::vector<string> edb;
    uint32_t table_size;

    //unsigned long get_index(const string& keyword, unsigned short ind);

public:
    ClientHandler(float alpha);
    ~ClientHandler();
    int stash_len;
    unsigned long get_index(const string& keyword, unsigned short ind);
    int setup(int size, string& seedstr, vector<kv> db);
    vector<string> get_edb();
    vector<string> get_estash();
    void update(const string& keyword, int ind, OP op, string& text);
    void upload();
    vector<GGMNode> getToken_min_coverage(const string& keyword, int length, uint8_t* prf_seed);
    vector<GGMNode> getToken(const string& keyword, int length, uint8_t* prf_seed);
    int addEDB(int size, string& seedstr, vector<string> plains);
};


#endif //CLIENTHANDLER_H

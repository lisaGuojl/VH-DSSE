#pragma once


#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <functional>
#include "GGMTree.h"
#include "cuckoo.h"

#include "ServerHandler.h"
using namespace cuckoo;

enum OP {
    INS, DEL
};

class ClientHandler {
private:
    uint8_t* key = (unsigned char*)"0123456789123456";
    uint8_t* iv = (unsigned char*)"0123456789123456";
    uint8_t* prf_seed = (unsigned char*)"0123456789123456";


    GGMTree* tree;
    KukuTable* table;
    std::vector<string> stash;
    std::vector<string> edb;
    uint32_t table_size;
  

    ServerHandler* server;


public:
    ClientHandler(int size, float alpha);
    ~ClientHandler();
    int stash_len;
    unsigned long get_index(const string& keyword, unsigned short ind);
    void update(const string& keyword, int ind, string& text);
    void upload();
    vector<string> search(const string& keyword, int length);
};


#endif //CLIENTHANDLER_H

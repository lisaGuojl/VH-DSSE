#ifndef PUNCTURABLE_PRF_GGMNODE_H
#define PUNCTURABLE_PRF_GGMNODE_H
#include "Utils.h"
//extern "C" {
//#include "Utils.h"
//}

class GGMNode {
public:
    long index;
    int level;
    uint8_t digest[16]{};

    GGMNode(unsigned long index, int level) {
        this->index = index;
        this->level = level;
    }

    GGMNode(unsigned long index, int level, uint8_t* digest) {
        this->index = index;
        this->level = level;
        memcpy(this->digest, digest, AES_BLOCK_SIZE);
    }
};


#endif
#ifndef ABSTRACT_H
#define ABSTRACT_H

#include "../lib/hash.h"
#include "../lib/Util.h"

class Sketch{
public:
    std::string NAME;
    uint64_t MEMORY;

    Sketch(){}
    virtual ~Sketch(){};

    virtual void Insert(const ItemPair& item) = 0;
    virtual HashMap Report(COUNT_TYPE HIT) = 0;
};

#endif

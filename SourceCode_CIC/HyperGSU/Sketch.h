#ifndef SKETCH_H
#define SKETCH_H

#include "../lib/hash.h"
#include "../lib/Util.h"

class Sketch {
public:
    Sketch() {}
    std::string NAME;//Sketch名称
    uint64_t MEMORY;//占用内存
    virtual ~Sketch() {};
    virtual void Insert(const ItemPair& item) = 0;//插入函数，若存在攻击batch则插入到GSU
    virtual HashMap Report(COUNT_TYPE HIT) = 0;//报告Top-K元素，频率阈值为HIT
};

#endif
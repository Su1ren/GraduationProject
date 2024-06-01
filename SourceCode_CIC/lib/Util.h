#ifndef UTIL_H
#define UTIL_H

#include <unordered_map>
#include <cstdint>
#include "hash.h"
#include <cstring>
#include <chrono>
#include <sstream>
//#define DELTA 1000

typedef uint32_t DATA_TYPE;//IP地址
typedef uint32_t TIME_TYPE;//Unix时间戳：用32位无符号整数
typedef int32_t COUNT_TYPE;

struct ItemPair{
    
    DATA_TYPE item;
    TIME_TYPE time;
    ItemPair(DATA_TYPE _item = 0, TIME_TYPE _time = 0):
        item(_item), time(_time){}
    static std::string Uint32ToIpAddress(uint32_t ip) {
        std::stringstream ss;
        ss << (ip & 0xFF) << '.'
           << ((ip >> 8)  & 0xFF) << '.'
           << ((ip >> 16) & 0xFF) << '.'
           << ((ip >> 24) & 0xFF);
        return ss.str();
    }
    friend std::ostream& operator<<(std::ostream& out,const ItemPair& p) {
        out << Uint32ToIpAddress(p.item) << "\tat " << p.time;
        return out;
    }

};

bool operator == (const ItemPair& a, const ItemPair& b){
    return memcmp(&a, &b, sizeof(ItemPair)) == 0;
}

namespace std{
    template<>
    struct hash<ItemPair>{
        size_t operator()(const ItemPair& item) const noexcept
        {
            return Hash::BOBHash32((uint8_t*)&item, sizeof(ItemPair), 0);
        }
    };
}

typedef std::unordered_map<ItemPair, COUNT_TYPE> HashMap;

typedef std::chrono::high_resolution_clock::time_point TP;

using TopK = std::pair<ItemPair,COUNT_TYPE>;

inline TP now(){
    return std::chrono::high_resolution_clock::now();
}

inline double durations(TP finish, TP start){
    /*
        时钟周期1μs
    */
    return std::chrono::duration_cast<std::chrono::duration<double,std::ratio<1,1000000>>>(finish - start).count();
}

#endif

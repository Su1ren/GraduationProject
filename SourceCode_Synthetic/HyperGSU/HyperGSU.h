#ifndef HYPERGSU_H
#define HYPERGSU_H

#include "Sketch.h"
#define TIME_THRESHOLD 100
#define FREQ_THRESHOLD 20
#define CELLNUM 8
#define EXPIRED (2 * min_count)


template<uint32_t HASH_NUM = 2>
class HyperGSU : public Sketch {

public:
    /*
        HyperGSU Sketch 数据结构。
        每个ExCover bucket包含一个ID，到达时间，以及访问次数。
        根据论文的介绍，HASH_NUM缺省为2。

        第二部分是GSU的结构，单一散列表，每个bucket含多个CELL，维护一个置换失败次数信息。
        基于LRU思想的置换
        为了避免GSU先入为主的缺陷，设计一个LRU思想。
        GSU每个bucket中累计的高频的元素如果长期没有更新频率——定义为tfail达到两倍fmin及以上。
        则将其置换的对象从最小频率数据项变成当前队首的元素。定期清理失去流行的元素。
        这种达到阈值的清理不用更新最小频率的cell，因为必然不会是最小的被更新。

        判断清除的基准是，单个bucket中频率计数达到两倍fmin及以上的数据项，其中选出最久未更新的数据项索引。
        最久也就是新数据项和上次置换发生的时间戳的之差，其中的最大索引。
        更新可以是：
        1、频率++；
        2、该位置发生替换。
        之后，该位置的更新时间戳也更新。

    */
    struct bucket {
        //DATA_TYPE item;//数据元素ID
        TIME_TYPE arrival;//到达时间
        COUNT_TYPE count;//访问次数
    };

    struct GSU {
        struct Cell {
            DATA_TYPE item;//CELL中的itemID
            TIME_TYPE interval;//重复间隔
            COUNT_TYPE count;//重复次数
            TIME_TYPE last_change;//最近更新时间
        };

        Cell cells[CELLNUM];//CELL数组
        COUNT_TYPE fail;//bucket中的置换失败次数
    };

    HyperGSU(uint32_t _Memory,double ratio = 0.20,std::string_view _Name = "HyperGSU") {
        /*
            HyperGSU初始化，读取Sketch名称，确定内存大小，初始化散列表。
        */
        std::cout << "Ongoing " << '\n';
        NAME = _Name;
        MEMORY = _Memory;

        EXCOVER_LENGTH = _Memory * ratio / HASH_NUM / sizeof(bucket);
        GSU_LENGTH = _Memory * (1 - ratio) / sizeof(GSU);

        for(auto i = 0;i < HASH_NUM;i++) {
            buckets[i] = new bucket[EXCOVER_LENGTH];
            memset(buckets[i],0,sizeof(bucket) * EXCOVER_LENGTH);
        }

        gsu = new GSU[GSU_LENGTH];
        memset(gsu,0,sizeof(GSU) * GSU_LENGTH);
    }

    ~HyperGSU() {
        for(auto i = 0;i < HASH_NUM;i++)
            delete[] buckets[i];
        delete [] gsu;
    }

    void Insert(const ItemPair& item) {
        TIME_TYPE min_t = UINT32_MAX;
        bool has_batch = false;
        /*
        static int times{};
        if(times < 10) {
            std::cout << item << '\n';
            ++times;
        }
        */
        for(uint32_t i = 0;i < HASH_NUM;++i) {
            uint32_t position = hash(item.item,i) % EXCOVER_LENGTH;
            bucket dst_bucket = buckets[i][position];
            //std::cout << dst_bucket.arrival << ' ' << dst_bucket.count << '\n';
            if(dst_bucket.count == 0 || (item.time - dst_bucket.arrival < TIME_THRESHOLD && dst_bucket.count < FREQ_THRESHOLD)) {
                ++buckets[i][position].count;
                buckets[i][position].arrival = item.time;
                continue;
            }
            else if(item.time - dst_bucket.arrival >= TIME_THRESHOLD && dst_bucket.count < FREQ_THRESHOLD) {
                min_t = MIN(min_t,buckets[i][position].arrival);
                buckets[i][position].arrival = item.time;
                buckets[i][position].count = 0;
                //std::cout << "Not batch\n";
            }
            else if(dst_bucket.count >= FREQ_THRESHOLD){
                min_t = MIN(min_t,buckets[i][position].arrival);
                buckets[i][position].arrival = item.time;
                buckets[i][position].count = 0;
                has_batch = true;
                //std::cout << "Batch found." << item.time << '\n';
            }
        }
        //std::cout << item.time - min_t << '\n';
        if(!has_batch)//不存在攻击batch，不需要存到HyperGSU中去
            return ;
        //std::cout << "Inserting..." << '\n';
        //存在攻击batch，插入到HyperGSU中去
        ItemPair E(item.item,(item.time < min_t) ? min_t - item.time : item.time - min_t);
        uint32_t position = hash(E,HASH_NUM) % GSU_LENGTH;
        uint32_t min_pos = 0,exp_pos = 0;
        COUNT_TYPE min_count = INT32_MAX;
        TIME_TYPE exp_time = UINT32_MAX;

        //查询bucket对应cells中是否存在对应元素和间隔，找到则频率++
        for(uint32_t j = 0;j < CELLNUM;++j) {
            if(gsu[position].cells[j].item == E.item &&
                gsu[position].cells[j].interval == E.time) {
                    ++gsu[position].cells[j].count;
                    gsu[position].cells[j].last_change = item.time;//对应cell发生更新
                    return ;
            }//找到了对应的数据项记录，对应++

            if(gsu[position].cells[j].count < min_count) {
                min_count = gsu[position].cells[j].count;
                min_pos = j;
            }//更新当前频率最低元素。
            if(gsu[position].cells[j].last_change < exp_time) {
                exp_time = gsu[position].cells[j].last_change;
                exp_pos = j;
            }
        }

        static long common{};
        static long expire{};
        static long fail{};
        //不存在于HyperGSU中，需要插入进去
        if(rng() % (2 * min_count - gsu[position].fail + 1) == 0) {//置换
            if(min_count != 0 && gsu[position].fail >= EXPIRED) {//基于长期未更新的置换
                //std::cout << "Expire update times " << ++expire << '\n';
                //std::cout << gsu[position].fail << ' ' << EXPIRED << '\n';
                //std::cout << ItemPair(gsu[position].cells[exp_pos].item,gsu[position].cells[exp_pos].interval) << ' ' << gsu[position].cells[exp_pos].count << '\n';
                gsu[position].cells[exp_pos].item = E.item;
                gsu[position].cells[exp_pos].interval = E.time;
                gsu[position].cells[exp_pos].last_change = item.time;
                gsu[position].cells[exp_pos].count = gsu[position].cells[min_pos].count + gsu[position].fail / gsu[position].cells[min_pos].count;
                gsu[position].fail = 0;
                return ;
            }
            //一般的概率性置换
            //std::cout << "Common update times " << ++common << '\n';
            gsu[position].cells[min_pos].item = E.item;
            gsu[position].cells[min_pos].interval = E.time;
            gsu[position].cells[min_pos].last_change = item.time;
            if(min_count == 0)//更新fmin
                gsu[position].cells[min_pos].count = 1;
            else
                gsu[position].cells[min_pos].count += gsu[position].fail / gsu[position].cells[min_pos].count;
            gsu[position].fail = 0;
        }else {//不置换
            ++gsu[position].fail;
            //std::cout << "Update fails times " << ++fail << '\n';
        }
    }

    HashMap Report(COUNT_TYPE HIT) {
        HashMap re{};

        for(uint32_t i = 0;i < GSU_LENGTH;++i) {
            for(uint32_t j = 0;j < CELLNUM;++j) {
                //std::cout << gsu[i].cells[j].count << std::endl;
                if(gsu[i].cells[j].count > HIT) {
                    //std::cout << gsu[i].cells[j].interval << '\n';
                    re[ItemPair(gsu[i].cells[j].item,\
                            gsu[i].cells[j].interval)] \
                    = gsu[i].cells[j].count;
                }
            }
        }
        return std::move(re);
    }

private:
    uint32_t EXCOVER_LENGTH;//每列ExCover哈希函数的bucket总数。
    uint32_t GSU_LENGTH;//HyperGSU中的bucket个数。
    bucket* buckets[HASH_NUM];//ExCover的bucket。
    GSU* gsu;//HyperGSU中的bucket阵列
};


#endif
#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <sys/stat.h>
#include <fstream>
#include <chrono>
#include <vector>
#include "./PeriodicSketch/PeriodicSketch.h"
#include "./HyperGSU/HyperGSU.h"
#include "./PeriodicSketch/MMap.h"
#include "./PeriodicSketch/Baseline.h"

#define F1SCORE(pr,rr) ((2 * pr * rr) / (pr + rr))

class BenchMark {
public:
    using AbsVector = std::vector<Sketch*>;
    BenchMark(const char* _PATH):PATH(_PATH) {
        result = Load(PATH);

        start = static_cast<ItemPair*>(result.start);

        //以下为PeriodicSketch的测试环节，需要做出改进
        SIZE = result.length / sizeof(ItemPair);
        TOTAL = SIZE;

        /* std::unordered_map<DATA_TYPE,TIME_TYPE> last_time;

        for(uint32_t i {0};i < SIZE;++i) {
            //start[i].time /= DELTA;
            if(last_time.find(start[i].item) != last_time.end()) {// 找到了
                TIME_TYPE interval = start[i].time - last_time[start[i].item];
                mp[ItemPair(start[i].item,interval)] += 1; 
            }
            last_time[start[i].item] = start[i].time;//进入时间保存
        } */
    }

    ~BenchMark() {
        UnLoad(result);
    }

    void BenchInsert(AbsVector& sketches) {
        
        /* for(uint32_t i {0};i < SIZE;++i) {
            for(auto& sketch: sketches)
                //InsertThp(sketch);
                sketch->Insert(start[i]);
        } */
        for(auto& sketch:sketches) {
            TP initial,finish;
            initial = now();
            for(uint32_t i{0};i < SIZE;++i) {
                sketch->Insert(start[i]);
            }
            finish = now();
            std::cout << sketch->NAME << " Insertion Thp: " << SIZE / durations(finish,initial) << std::endl;
        }

        
    }

    void InsertThp(Sketch* sketch) {
        TP initial,finish;
        
        initial = now();
        for(uint32_t i {0};i < SIZE;++i) {
            sketch->Insert(start[i]);
        }
        finish = now();

        std::cout << "Insertion Thp: " << SIZE / durations(finish,initial) << std::endl;
    }

    TopK printStat(const HashMap& temp) const {
        ItemPair suspended_ldos{};
        COUNT_TYPE cnt{0};
        for(auto it = temp.begin();it != temp.end();++it) {
            //std::cout << it->first << "\ttimes " << it->second << '\n'; 
            if(it->second > cnt) {
                suspended_ldos = it->first;
                cnt = it->second;
            }
        }
        std::cout << "The most possible LDoS Source: " << suspended_ldos << '\n';
        return {suspended_ldos,cnt};
    }

    void CheckError(Sketch* sketch,uint32_t HIT) {
        /*
            real：报告正确的记录数
            whole：所有报告的记录数
            LDOS_TRAFFIC：数据集中的所有LDoS攻击流量记录总总数
            LDOS_IP：代表真正的攻击流量源IP

        */
        double real = 0,whole = 0;
        double pr = 0,rr = 0,f1 = 0;

        HashMap temp = sketch->Report(HIT);
        
        
        for(auto it = temp.begin();it != temp.end();++it) {
            if(it->second > HIT) {
                //std::cout << "Adding " << it->second << '\n';
                if(it->first.item == LDOS_IP) {
                    real += it->second;
                }
                whole += it->second;
            }
        }
        TopK ldos = printStat(temp);
        std::cout << ldos.second << '\n';
        
        rr = (sketch->NAME == "HyperGSU Sketch") ? static_cast<double>(ldos.second) / LDOS_TRAFFIC : static_cast<double>(ldos.second) / (LDOS_TRAFFIC * FREQ_THRESHOLD);

        if(real <= 0) {
            std::cout << "Not Find" << std::endl;
        } else {
            pr = real / whole;
        }

        std::cout << "Precision Rate " << pr << '\n'
                  << "Recall Rate " << rr << '\n'
                  << "F1 Score " << F1SCORE(pr,rr) << std::endl;
    }

    void TopKError(double alpha) {
        AbsVector FPIs = {
            new HyperGSU<3>(chunk * 5,0.2),
            //new PeriodicSketch<3>(chunk * 50,0.2),
            //new Baseline(chunk * 30)
        };

        BenchInsert(FPIs);

        for(auto FPI: FPIs) {
            std::cout << "Check, " << FPI->NAME << " , " << FPI->MEMORY << std::endl;
            CheckError(FPI,alpha * TOTAL);
            std::cout << TOTAL * alpha << '\n';
            std::cout << std::endl;
            delete FPI;
        }
    }

private:
    LoadResult result;
    ItemPair* start;

    uint64_t SIZE{};
    double TOTAL{};

    HashMap mp;
    const char* PATH{};
    constexpr static COUNT_TYPE LDOS_TRAFFIC = 21589;
    constexpr static DATA_TYPE LDOS_IP = 16781484;
    constexpr static size_t chunk = 1024;
};

#endif
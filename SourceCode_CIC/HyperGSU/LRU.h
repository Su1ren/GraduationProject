#ifndef LRU_H
#define LRU_H

#include<queue>
/*
    基于LRU思想的置换
    为了避免GSU先入为主的缺陷，设计一个LRU思想。
    GSU每个bucket中累计的高频的元素如果长期没有更新频率
    则将其置换的对象从最小频率数据项变成当前队首的元素。定期清理失去流行的元素。

    长期——定义为tfail达到恰好两倍fmin。

    判断清除的基准是，单个bucket中频率计数达到两倍fmin及以上的数据项，其中选出最久未更新的数据项索引。
    最久也就是新数据项和上次置换发生的时间戳的之差，其中的最大索引。
    更新可以是：
    1、频率++；
    2、该位置发生替换。
    之后，该位置的更新时间戳也更新。

    逻辑结构上，GSU中的bucket中每个cell需要额外一个时间戳。
*/
class LruHeap {
public:
    //std::priority_queue
};

#endif
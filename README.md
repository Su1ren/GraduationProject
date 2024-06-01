# 总述

本文是关于实验的收集和分析内容，做了必要的预处理。

由于攻击检测部署在目标主机上，所以可以数据集中的目标地址应该都是本机。又因为网络数据中LDoS攻击大多是发生在传输层和应用层，所以需要记录的大概就是源IP地址加上端口号。但是根据数据集的LDoS流量分析，攻击流量往往是在固定IP地址上发动的，发动时会用大量不同端口发送流量，而在间歇期该地址不会发送任何数据，所以源端口不需要记录了。为了方便对齐，目的端口也不记录了，所以可以就用一个IP地址和时间戳来确定。

然后是如何将csv数据集变成二进制文件来缩减数据规模方便读取。由于C++在这一方面比较笨拙，所以数据集的处理全部是使用pandas库在本地处理的，经过淘洗、时间戳处理之后，转换为示例的CAIDA.dat类似的格式。

此外是BSketch代码部分，分为使用CIC数据集和合成数据集的两份。

# 结构梳理

分为五个板块：

CIC-IDS2017：CIC-IDS2017网络数据集，也是参数和对比试验的使用的数据集。

Synthetic：基于论文在 NS-3 上采集的数据。

其他流量集：如SUEE等其他未使用的pcap流量文件。

预处理：对CIC-IDS2017的处理程序。

参数实验：确定最佳参数d和r的测试程序和数据处理程序。

对比实验：PeriodicSketch和BSketch的性能对比实验数据收集与处理。

SourceCode_CIC：使用CIC数据集的实验代码

SourceCode_Synthetic：使用模拟数据集的实验代码



# CIC-IDS2017

原始csv文件：ldos.csv   extract.py处理提取源IP，时间，标签三列	       得到output.csv

output.csv：	            timestamp.py处理将日期转为Unix时间	          得到timestamp.csv

timestamp.py		  另拷贝一份作为效果验证				           得到check.csv

​					  binarize.py将IP地址和时间戳以二进制写入     得到u32.dat和u64.dat(按时间戳格式区分)

由于上传数据大小限制，而且原始数据集开放，ldos.csv没有一同上传。 

# 其他流量集

slowread1、2：包含slowread攻击流量的pcap数据集。

SUEE1：包含LDoS攻击流量的在线数据集。尺寸过大也不一同上传。

以上的3个数据集都未在本次实验中使用。



# 预处理

分为 CIC 和 SYNTHETIC。

CIC：

extract.py，timestamp.py，binarize.py见CIC-IDS2017节。

ratio.py：根据CIC-IDS2017数据集分析结果的处理。

SYNTHETIC：

syntheticx.csv：三份模拟数据集

binarize.py：将数据集转为二进制文件。

# 参数实验

parameter_d，u32_dtest：关于参数d的测试程序和数据收集。

parameter_r，u32_rtest：关于参数r的测试程序和数据收集。



# 对比实验

分为使用 CIC 和 模拟数据集的实验结果。

contrast.csv：采集到的性能指标

contrast.py：对比图示

# Synthetic

模拟数据集相关内容。

MA_Thesis_Pascal_Kiechl.pdf：实验参考论文。

SYN1_x.dat：单次攻击流量的记录重复频率

syntheticx.csv：同预处理节同名文件

数据集参数设置：LDoS攻击模拟出现的实际

# SourceCode_xxx

BSketch的实验代码，分为使用CIC数据集和合成数据集的两种。

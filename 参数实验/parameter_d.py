import pandas as pd
import matplotlib.pyplot as plt

hashNum = [1,2,3,4,5]

pr1 = [0.951586,0.962722,0.957499,0.953313,0.955006]
pr2 = [0.947737,0.947432,0.961159,0.963114,0.954902]
pr3 = [0.932953,0.937081,0.950221,0.947803,0.940685]
pr4 = [0.942846,0.942663,0.939893,0.955839,0.94348]
pr5 = [0.932326,0.935725,0.9397,0.93932,0.948408]

rr1 = [0.213952,0.377137,0.524897,0.63764,0.597943] 
rr2 = [0.219232,0.401547,0.563945,0.689379,0.761082]
rr3 = [0.219788,0.413914,0.56677,0.697253,0.709621]
rr4 = [0.220066,0.418083,0.554125,0.710825,0.697439]
rr5 = [0.220158,0.383019,0.546436,0.643893,0.767196]

tp1 = [34.8964,19.8513,13.1407,10.3631,8.41816]
tp2 = [35.4775,18.434,13.6768,10.016,8.30179]
tp3 = [37.0562,19.0449,13.603,10.8624,8.25784]
tp4 = [35.3112,19.8509,13.6592,10.6827,7.96015]
tp5 = [35.2309,18.9519,14.1302,10.6615,8.27764]

fig = plt.figure()
ax1 = fig.add_subplot(1,3,1)
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False
#PR
ax1.plot(hashNum,pr1,label='1KB')
ax1.plot(hashNum,pr2,label='2KB')
ax1.plot(hashNum,pr3,label='3KB')
ax1.plot(hashNum,pr4,label='4KB')
ax1.plot(hashNum,pr5,label='5KB')

ax1.legend()
ax1.set_xlabel('哈希表数目d')
ax1.set_ylabel('准确率')
ax1.set_title('准确率')
ax1.tick_params(axis='both', direction='in')


#RR
ax2 = fig.add_subplot(1,3,2)
ax2.plot(hashNum,rr1,label='1KB')
ax2.plot(hashNum,rr2,label='2KB')
ax2.plot(hashNum,rr3,label='3KB')
ax2.plot(hashNum,rr4,label='4KB')
ax2.plot(hashNum,rr5,label='5KB')

ax2.legend()
ax2.set_xlabel('哈希表数目d')
ax2.set_ylabel('召回率')
ax2.set_title('召回率')
ax2.tick_params(axis='both', direction='in')

ax3 = fig.add_subplot(1,3,3)
ax3.plot(hashNum,tp1,label='1KB')
ax3.plot(hashNum,tp2,label='2KB')
ax3.plot(hashNum,tp3,label='3KB')
ax3.plot(hashNum,tp4,label='4KB')
ax3.plot(hashNum,tp5,label='5KB')

ax3.legend()
ax3.set_xlabel('哈希表数目d')
ax3.set_ylabel('吞吐率')
ax3.set_title('吞吐率')
ax3.tick_params(axis='both', direction='in')

plt.tight_layout()
plt.show()
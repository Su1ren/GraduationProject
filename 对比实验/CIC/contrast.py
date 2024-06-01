import matplotlib.pyplot as plt

memory = [1,2,3,4,5]

pr_b = [0.944421,0.966516,0.94973,0.941396,0.9413]
rr_b = [0.507666,0.50674,0.554125,0.573672,0.560795]
tp_b = [13.726,13.1498,13.5704,13.7986,13.464]
f1_b = [0.66036,0.664884,0.699893,0.712908,0.702853]

pr_p = [0.597607,0.596957,0.596705,0.596387,0.595868]
rr_p = [0.232492,0.232621,0.232641,0.232726,0.232481]
tp_p = [11.7271,11.4338,10.9143,11.2196,10.7842]
f1_p = [0.334752,0.334784,0.334765,0.334803,0.334468]

fig = plt.figure()
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False

ax1 = fig.add_subplot(2,2,1)
ax1.plot(memory,pr_b,label='BSketch')
ax1.plot(memory,pr_p,label='PeriodicSketch')
ax1.legend()
ax1.set_xlabel('内存开销(KB)')
ax1.set_ylabel('准确率')
#ax1.set_ybound(0.5,1)
ax1.set_title('(a) 准确率')
ax1.tick_params(axis='both', direction='in')

ax2 = fig.add_subplot(2,2,2)
ax2.plot(memory,rr_b,label='BSketch')
ax2.plot(memory,rr_p,label='PeriodicSketch')
ax2.legend()
ax2.set_xlabel('内存开销(KB)')
ax2.set_ylabel('召回率')
ax2.set_ybound(0.2,0.6)
ax2.set_title('(b) 召回率')
ax2.tick_params(axis='both', direction='in')

ax3 = fig.add_subplot(2,2,3)
ax3.plot(memory,tp_b,label='BSketch')
ax3.plot(memory,tp_p,label='PeriodicSketch')
ax3.legend()
ax3.set_xlabel('内存开销(KB)')
ax3.set_ylabel('吞吐率')
ax3.set_ybound(10,14)
ax3.set_title('(c) 吞吐率')
ax3.tick_params(axis='both', direction='in')

ax4 = fig.add_subplot(2,2,4)
ax4.plot(memory,f1_b,label='BSketch')
ax4.plot(memory,f1_p,label='PeriodicSketch')
ax4.legend()
ax4.set_xlabel('内存开销(KB)')
ax4.set_ylabel('F1分数')
ax4.set_ybound(0.3,0.8)
ax4.set_title('(d) F1分数')
ax4.tick_params(axis='both', direction='in')

plt.tight_layout()

plt.show()
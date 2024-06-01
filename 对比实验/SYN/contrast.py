import matplotlib.pyplot as plt

memory = [10,20,30,40,50]

pr_b = [0.994958,0.984759,0.991291,0.9823,0.985977]
rr_b = [0.307988,0.486113,0.560309,0.608532,0.621858]
tp_b = [10.428,9.75819,10.1135,10.5087,10.515]
f1_b = [0.470373,0.650912,0.715944,0.751507,0.762688]

pr_p = [0.555839,0.471241,0.602797,0.766072,0.819468]
rr_p = [0.259765,0.260005,0.259963,0.259883,0.259903]
tp_p = [6.62685,6.48504,6.49614,6.53514,6.51372]
f1_p = [0.354062,0.335113,0.363264,0.388105,0.394641]

fig = plt.figure()
plt.rcParams['font.sans-serif'] = ['SimHei'] 
plt.rcParams['axes.unicode_minus'] = False

ax1 = fig.add_subplot(2,2,1)
ax1.plot(memory,pr_b,label='BSketch')
ax1.plot(memory,pr_p,label='PeriodicSketch')
ax1.legend()
ax1.set_xlabel('内存开销 (KB)')
ax1.set_ylabel('准确率')
ax1.set_ybound(0.4,)
ax1.set_title('(a) 准确率')
ax1.tick_params(axis='both', direction='in')

ax2 = fig.add_subplot(2,2,2)
ax2.plot(memory,rr_b,label='BSketch')
ax2.plot(memory,rr_p,label='PeriodicSketch')
ax2.legend()
ax2.set_xlabel('内存开销 (KB)')
ax2.set_ylabel('召回率')
ax2.set_ybound(0.2,0.7)
ax2.set_title('(b) 召回率')
ax2.tick_params(axis='both', direction='in')

ax3 = fig.add_subplot(2,2,3)
ax3.plot(memory,tp_b,label='BSketch')
ax3.plot(memory,tp_p,label='PeriodicSketch')
ax3.legend()
ax3.set_xlabel('内存开销 (KB)')
ax3.set_ylabel('吞吐率')
ax3.set_ybound(6,12)
ax3.set_title('(c) 吞吐率')
ax3.tick_params(axis='both', direction='in')

ax4 = fig.add_subplot(2,2,4)
ax4.plot(memory,f1_b,label='BSketch')
ax4.plot(memory,f1_p,label='PeriodicSketch')
ax4.legend()
ax4.set_xlabel('内存开销 (KB)')
ax4.set_ylabel('F1分数')
ax4.set_ybound(0.3,0.8)
ax4.set_title('(d) F1分数')
ax4.tick_params(axis='both', direction='in')

plt.tight_layout()

plt.show()

def improvement(bsketch,pre):
    print((sum(bsketch) / len(bsketch)) / (sum(pre) / len(pre)) - 1)

""" improvement(pr_b,pr_p)
improvement(rr_b,rr_p)
improvement(tp_b,tp_p)
improvement(f1_b,f1_p)
print(sum(f1_p) / len(f1_p)) """
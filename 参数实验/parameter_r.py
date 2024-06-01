import matplotlib.pyplot as plt

r = [0.1,0.2,0.3,0.4,0.5]

pr1 = [0.9413,0.949349,0.942551,0.95466,0.961784]
pr2 = [0.949349,0.95466,0.951249,0.949494,0.966595]
pr3 = [0.942551,0.951249,0.945137,0.937209,0.921459]
pr4 = [0.95466,0.949494,0.932709,0.953346,0.956122]
pr5 = [0.961784,0.966595,0.921459,0.956122,0.922469]

rr1 = [0.560795,0.573857,0.435453,0.594933,0.627171]
rr2 = [0.573857,0.594953,0.433832,0.447589,0.627264]
rr3 = [0.435453,0.423832,0.379036,0.317338,0.237482]
rr4 = [0.594933,0.447589,0.317338,0.433508,0.453194]
rr5 = [0.627171,0.627264,0.237482,0.453194,0.238084]

tp1 = [14.1901,13.9844,13.8643,14.5398,14.2727]
tp2 = [13.9343,13.9946,14.1236,14.3478,13.5489]
tp3 = [14.4933,13.2198,14.6268,14.4333,14.8638]
tp4 = [14.4341,14.4237,15.4122,14.6163,14.2977]
tp5 = [13.8148,14.3882,14.1785,14.5764,15.0667]

fig = plt.figure()
ax1 = fig.add_subplot(1,3,1)
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False
#PR
ax1.plot(r,pr1,label='10KB')
ax1.plot(r,pr2,label='20KB')
ax1.plot(r,pr3,label='30KB')
ax1.plot(r,pr4,label='40KB')
ax1.plot(r,pr5,label='50KB')

ax1.legend()
ax1.set_xlabel('比例r')
ax1.set_ylabel('准确率')
ax1.set_title('准确率')
ax1.tick_params(axis='both', direction='in')


#RR
ax2 = fig.add_subplot(1,3,2)
ax2.plot(r,rr1,label='10KB')
ax2.plot(r,rr2,label='20KB')
ax2.plot(r,rr3,label='30KB')
ax2.plot(r,rr4,label='40KB')
ax2.plot(r,rr5,label='50KB')

ax2.legend()
ax2.set_xlabel('比例r')
ax2.set_ylabel('召回率')
ax2.set_title('召回率')
ax2.tick_params(axis='both', direction='in')

ax3 = fig.add_subplot(1,3,3)
ax3.plot(r,tp1,label='10KB')
ax3.plot(r,tp2,label='20KB')
ax3.plot(r,tp3,label='30KB')
ax3.plot(r,tp4,label='40KB')
ax3.plot(r,tp5,label='50KB')

ax3.legend()
ax3.set_xlabel('比例r')
ax3.set_ylabel('吞吐率')
ax3.set_title('吞吐率')
ax3.tick_params(axis='both', direction='in')

plt.tight_layout()
plt.show()


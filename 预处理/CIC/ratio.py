import matplotlib.pyplot as plt

labels = ['GoldenEye','Slowloris','Slowhttptest']
size = [10293,5796,5499]

plt.pie(size,labels=labels,autopct='%1.1f%%')

plt.title('LDoS')
plt.show()

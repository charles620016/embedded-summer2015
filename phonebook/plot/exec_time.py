# encoding=utf-8
import numpy as np
import matplotlib.pyplot as plt


N = 3
ind = np.arange(N)  # the x locations for the groups
width = 0.22       # the width of the bars

origin = (7.19, 89.89, 105.93)
optimal = (2.79, 66.02, 72.13)
hashing = (0.25, 68.72, 75.10)

fig, ax = plt.subplots()
rects1 = ax.bar(ind, origin, width, color='indianred')
rects2 = ax.bar(ind + width, optimal, width, color='seagreen')
rects3 = ax.bar(ind + 2*width, hashing, width, color='cornflowerblue')


# add some text for labels, title and axes ticks
ax.set_ylabel('execution time (ms)')
ax.set_title('Execution time of each version')
ax.set_xticks(ind+width)
ax.set_xticklabels( ('            findName()', '      append()', '       total time elapsed') )

ax.legend( (rects1[0], rects2[0], rects3[0]), ('origin', 'optimal', 'hash') )

def autolabel(rects):
    # attach some text labels
    for rect in rects:
        height = rect.get_height()
        ax.text(rect.get_x()+rect.get_width()/2., 1.05*height, '%.2f'%float(height),
                ha='center', va='bottom')

autolabel(rects1)
autolabel(rects2)
autolabel(rects3)

plt.show()
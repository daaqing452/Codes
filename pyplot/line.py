import numpy as np
import matplotlib.pyplot as plt
import sys


fig = plt.figure()
ax = fig.add_subplot(111)
box = ax.get_position()
ax.set_position([box.x0, box.y0 + 0.1, box.width, box.height * 0.9])
ax.grid(True)
x = (1, 2, 3, 4, 5)
y_free = (26.192960222, 26.739828278, 26.594411944, 26.896248444, 28.662818333)
y_focus = (19.536407333, 20.497774167, 21.355265389, 21.501691444, 22.664821056)
std_free = (5.3357401683, 5.12128703, 5.978533808, 4.3449451011, 6.0031973843)
std_focus = (3.0884598206, 3.716426245, 4.2527996196, 2.8917364563, 3.1447091482)
ax.set_xlim(0.01, 5.99)
# ax.set_ylim(0, 25)
ax.set_ylim(0, 37)
line_focus = ax.errorbar(x, y_focus, yerr=std_focus, fmt='.-', color='#cc6666', markeredgecolor='#cc6666', marker='o')
line_free = ax.errorbar(x, y_free, yerr=std_free, fmt='.-', color='#33cc66', markeredgecolor='#33cc66',marker='s')
ax.set_ylabel('Input speed (WPM)')
ax.set_xlabel('Block')
names = ['Eyes-on', 'Peripheral']
ax.legend( (line_focus[0], line_free[0]), names, loc = 'lower right', prop = {'size':9}, ncol=3)
fig.set_size_inches(6, 3)
fig.savefig(sys.argv[0][:-3] + '.png', dpi = 300)
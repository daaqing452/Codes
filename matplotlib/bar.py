import matplotlib.pyplot as plt
import numpy as np
import sys

n = 3
mean_0 = 100*np.array((0.7495653889, 0.9227583333, 0.9783525))
mean_1 = 100*np.array((0.9225632222, 0.9902546111, 0.9932275556))
mean_2 = 100*np.array((0.9974259444, 0.9988916111, 0.9994337222))
std_0 = 100*np.array((0.1488989114, 0.0794279731, 0.0318138584))
std_1 = 100*np.array((0.0462600231, 0.0114472269, 0.0089043904))
std_2 = 100*np.array((0.0043414064, 0.0021355559, 0.0016494601))
ind = np.arange(n)
fig = plt.figure()
ax = fig.add_subplot(111)
# box = ax.get_position()
# ax.set_position([box.x0, box.y0, box.width * 0.5, box.height])
b = 0.15
w = 0.25
rect_0 = ax.bar(b + ind + w * 2, mean_0, w, color='#3366cc', yerr=std_0, ecolor='#000000')
rect_1 = ax.bar(b + ind + w * 1, mean_1, w, color='#33cc66', yerr=std_1, ecolor='#000000')
rect_2 = ax.bar(b + ind + w * 0, mean_2, w, color='#cc6666', yerr=std_2, ecolor='#000000')
ax.set_ylabel('Accuracy (%)')
ax.set_ylim(0, 105)
ax.yaxis.grid(True)
# ax.set_title('xxx')
ax.set_xticks(b + ind + w * 1.5)
ax.set_xticklabels( ('Top-1', 'Top-5', 'Top-25') )
names = ('Eyes-on', 'Peripheral', 'No-keyboard')
ax.legend( (rect_2[0], rect_1[0], rect_0[0]), names, loc = 'lower right', prop = {'size':10})
'''def autolabel(rects, stds):
	i = 0
	for rect in rects:
		height = rect.get_height()
		ax.text(rect.get_x() + rect.get_width() / 2., height + stds[i], '%.1f' % height, ha='center', va='bottom')
		i += 1
autolabel(rect_ag, std_ag)
autolabel(rect_ap, std_ap)
autolabel(rect_rg, std_rg)
autolabel(rect_rp, std_rp)'''
fig.set_size_inches(6, 3)
fig.savefig(sys.argv[0][:-3] + '.png', dpi = 300)
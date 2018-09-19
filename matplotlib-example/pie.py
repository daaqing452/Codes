from pylab import *
from matplotlib import font_manager as fm

fig = figure(1, figsize=(6, 6))
ax = axes([0.2, 0.2, 0.7, 0.7])

labels = 'Gaze-fixed\nIn-Vocabulary', 'Gaze-switching\nIn-Vocabulary', 'Gaze-fixed\nOut-Of-Vocabulary', 'Gaze-switching\nOut-Of-Vocabulary', 'Punctuations\nand dights', 'Others'
fracs = [0.3565869167, 0.233174, 0.0542275, 0.16188025, 0.1368115833, 0.0573198333]
explode=(0.05, 0, 0, 0, 0, 0)

patches, texts, autotexts = pie(fracs, explode=explode, labels=labels, autopct='%1.1f%%', shadow=True, #startangle=90,
	colors=('#cc3333', '#cc9966', '#cccc00', '#33cc33', '#33cccc', '#3333ff'))

ax.set_xlabel('Gaz In Ou ns', size=17)

proptease = fm.FontProperties()
proptease.set_size('x-large')
# plt.setp(autotexts, fontproperties=proptease)
plt.setp(texts, fontproperties=proptease)

# title('Raining Hogs and Dogs', bbox={'facecolor':'0.8', 'pad':5})

fig.savefig(sys.argv[0][:-3] + '.png', dpi = 300)
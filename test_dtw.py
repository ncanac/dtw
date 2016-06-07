from numpy.random import rand
from _dtw import dtw
import sys
import time

size = 10000
window = 0.1
if len(sys.argv) > 1:
    size = int(sys.argv[1])
    if len(sys.argv) > 2:
        window = float(sys.argv[2])

x = rand(size)
y = rand(size)

t0 = time.clock()
dist = dtw(x, y, window)
tf = time.clock()
print "DTW distance with window={}: {}".format(window, dist)
print "Took {} seconds.".format(tf - t0)

print ""

t0 = time.clock()
dist = dtw(x, y, size)
tf = time.clock()
print "DTW distance with no window: {}".format(dist)
print "Took {} seconds.".format(tf - t0)

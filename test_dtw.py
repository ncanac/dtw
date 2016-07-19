import numpy as np
from numpy.random import rand
from _dtw import dtw, dtw_path
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

#x = np.array([1, 1, 2, 3, 2, 0])
#y = np.array([0, 1, 1, 2, 3, 2, 1])

print "Computing DTW distance...\n"

t0 = time.clock()
dist = dtw(x, y, window)
tf = time.clock()
print "DTW distance with window={}: {}".format(window, dist)
print "Took {} seconds.".format(tf - t0)

print "\nComputing DTW path...\n"

t0 = time.clock()
path = dtw_path(x, y, window)
tf = time.clock()
print path[:5]
print "..."
print path[-5:]
assert np.isclose(sum([abs(x[xi] - y[yi]) for xi, yi in path]), dist)
#print sum([abs(x[xi] - y[yi]) for xi, yi in path])
print "Took {} seconds.\n".format(tf - t0)

print "Computing DTW distance...\n"

t0 = time.clock()
dist = dtw(x, y, 1.)
tf = time.clock()
print "DTW distance with no window: {}".format(dist)
print "Took {} seconds.".format(tf - t0)

print "\nComputing DTW path...\n"

t0 = time.clock()
path = dtw_path(x, y, 1.)
tf = time.clock()
print path[:5]
print "..."
print path[-5:]
assert np.isclose(sum([abs(x[xi] - y[yi]) for xi, yi in path]), dist)
#print sum([abs(x[xi] - y[yi]) for xi, yi in path])
print "Took {} seconds.".format(tf - t0)

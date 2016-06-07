# dtw
Dynamic time warping distance C extension for Python

## Installation

To compile and link the source code in the current directory, type:

```
python setup.py build_ext --inplace
```

If compilation is successful, you can run the small test script, which
generates two arrays of random numbers and computes the DTW distance between
them, first using a window constraint and then without one. The test script can
be run zero, one, or two position arguments.

```
Zero
----
Generates two arrays with 10000 elements and a window size of 0.1. This takes
about a second to run on my machine.

Example
    python test_dtw.py

One
---
Takes one command line argument, which is the size of the arrays.

Example
    python test_dtw.py 10000

Two
---
Takes two command line arguments. The first argument is the size of the arrays
and the second argument is the window fraction.

Example
    python test_dtw.py 10000 0.1

Example output
--------------

DTW distance with window=0.1: 1526.4299465
Took 0.362146 seconds.

DTW distance with no window: 1526.4299465
Took 0.772507 seconds.
```

## Description

Computes the dynamic time warping (DTW) distance between two sequences.

```
Parameters
----------
x : numpy array of floats
    First sequence
y : numpy array of floats
    Second sequence
window_frac: float
    Locality constraint, given as a fraction from 0 to 1 of the size of the
    larger sequence.

Returns
-------
float
    The DTW distance between x and y
```

## Usage

```
In [1]: import numpy as np

In [2]: from _dtw import dtw

In [3]: x = np.array([3, 2, 2, 1, 3, 1, 1])

In [4]: y = np.array([1, 1, 3, 2, 1, 2])

In [5]: dtw(x, y, 0.5)
Out[5]: 6.0
```

Also refer to example in test_dtw.py

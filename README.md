# dtw
Dynamic time warping distance C extension for Python

## Installation

python setup.py build_ext --inplace

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
    Locality constraint, given as a fraction of the size of the size of the
    second sequence.

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

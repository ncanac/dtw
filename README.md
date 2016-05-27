# dtw
Dynamic time warping distance C extension for Python

## Installation

python setup.py build_ext --inplace

## Description

Computes the dynamic time warping (DTW) distance between two sequences.

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

## Usage

```python
import numpy as np
from _dtw import dtw

x = np.array([])
y = np.array([])

dtw_dist = dtw(x, y, 0.2)
```

Also refer to example in test_dtw.py

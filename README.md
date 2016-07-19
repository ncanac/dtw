# dtw
Dynamic time warping (DTW) distance C extension for Python

## Installation

To compile and link the source code in the current directory, type:

```
python setup.py build_ext --inplace
```

or just execute the compilation script:

```
./compile_test
```

which will also run the test script.

## Testing

If compilation is successful, you can manually run the test script, which
generates two arrays of random numbers and computes the DTW distance and path
between them, first using a window constraint and then without one. The test
script can be run with zero, one, or two position arguments.

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
```

The test script test_dtw.py can be run as follows:

```
Example input
-------------
    python test_dtw.py 10000 0.1

Example output
--------------

Computing DTW distance...

DTW distance with window=0.1: 1528.85553244
Took 0.33991 seconds.

Computing DTW path...

[[9999 9999]
 [9998 9999]
 [9997 9999]
 [9996 9999]
 [9995 9999]]
...
[[1 4]
 [0 3]
 [0 2]
 [0 1]
 [0 0]]
Took 0.342164 seconds.

Computing DTW distance...

DTW distance with no window: 1528.85553244
Took 0.678301 seconds.

Computing DTW path...

[[9999 9999]
 [9998 9999]
 [9997 9999]
 [9996 9999]
 [9995 9999]]
...
[[1 4]
 [0 3]
 [0 2]
 [0 1]
 [0 0]]
Took 0.677329 seconds.
```

## Description

```
FUNCTIONS
    dtw(...)
        Compute the dynamic time warping (DTW) distance between two sequences.
        
        Parameters
        ----------
        x : numpy array of floats
           First sequence
        y : numpy array of floats
           Second sequence
        window_frac: float
           Locality constraint, given as a fraction from 0 to 1 of the size of
           the larger sequence.
        
        Returns
        -------
        float
           The DTW distance between x and y

    dtw_path(...)
        Determine the optimal warping between two sequences.
        
        Parameters
        ----------
        x : numpy array of floats
           First sequence
        y : numpy array of floats
           Second sequence
        window_frac: float
           Locality constraint, given as a fraction from 0 to 1 of the size of
           the larger sequence.
        
        Returns
        -------
        numpy.ndarray
           The pairings between the two sequences that provide the optimal
           warping path.
```

## Usage

```
In [1]: import numpy as np

In [2]: from _dtw import dtw, dtw_path

In [3]: x = np.array([3, 2, 2, 1, 3, 1, 1])

In [4]: y = np.array([1, 1, 3, 2, 1, 2])

In [5]: dtw(x, y, 0.5)
Out[5]: 6.0

In [6]: dtw.dtw_path(x, y, 0.5)
Out[6]: 
array([[6, 5],
       [5, 4],
       [4, 3],
       [4, 2],
       [3, 1],
       [2, 0],
       [1, 0],
       [0, 0]], dtype=int32)
```

Also refer to example in test_dtw.py

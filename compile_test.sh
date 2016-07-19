#!/bin/bash

python setup.py build_ext --inplace

python test_dtw.py

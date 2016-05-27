#include <Python.h>
#include <numpy/arrayobject.h>
#include "dtw.h"

/* Docstrings */
static char module_docstring[] =
    "This module provides an interface for calculating the DTW distance in C.";
static char dtw_docstring[] =
    "Calculate the DTW distance between two state sequences.";

/* Available functions */
static PyObject *dtw_dtw(PyObject *self, PyObject *args);

/* Module specification */
static PyMethodDef module_methods[] = {
    {"dtw", dtw_dtw, METH_VARARGS, dtw_docstring},
    {NULL, NULL, 0, NULL}
};

/* Initialize the module */
PyMODINIT_FUNC init_dtw(void)
{
    PyObject *m = Py_InitModule3("_dtw", module_methods, module_docstring);
    if (m == NULL)
        return;

    import_array();
}

static PyObject *dtw_dtw(PyObject *self, PyObject *args)
{
    double window_frac;
    PyObject *x_obj, *y_obj;

    /* Parse the input tuple */
    if(!PyArg_ParseTuple(args, "OOd", &x_obj, &y_obj, &window_frac))
        return NULL;

    /* Interpret the input objects as numpy arrays. */
    PyObject *x_array = PyArray_FROM_OTF(x_obj, NPY_DOUBLE, NPY_IN_ARRAY);
    PyObject *y_array = PyArray_FROM_OTF(y_obj, NPY_DOUBLE, NPY_IN_ARRAY);

    /* If that didn't work, throw an exception. */
    if(x_array == NULL || y_array == NULL)
    {
        Py_XDECREF(x_array);
        Py_XDECREF(y_array);
        return NULL;
    }

    /* Get the number of data points in each array */
    int xsize = (int)PyArray_DIM(x_array, 0);
    int ysize = (int)PyArray_DIM(y_array, 0);

    /* Get pointers to the data as C-types. */
    double *x = (double*)PyArray_DATA(x_array);
    double *y = (double*)PyArray_DATA(y_array);

    /* Call the external C function to compute the DTW distance. */
    double value = dtw(x, y, xsize, ysize, window_frac);

    /* Clean up. */
    Py_DECREF(x_array);
    Py_DECREF(y_array);

    if(value < 0.0)
    {
        PyErr_SetString(PyExc_RuntimeError,
                    "dtw returned an impossible value.");
        return NULL;
    }

    /* Build the output tuple */
    PyObject *ret = Py_BuildValue("d", value);
    return ret;
}

#include "samp.h"

static PyObject* wrapper_calc_area(PyObject* self, PyObject* args)
{
    double x_min, x_max, y_min, y_max;
    int n_x, n_y, it_min, it_max;
    int thread, seed;

    if(!PyArg_ParseTuple(
        args, "ddddiiiiii",
        &x_min, &x_max, &y_min, &y_max,
        &n_x, &n_y, &it_min, &it_max,
        &thread, &seed
    ))
        return NULL;

    omp_set_num_threads(thread);

    init_array();

    double a = calc_area(x_min, x_max, y_min, y_max, n_x, n_y, it_min, it_max, seed);
    
    return Py_BuildValue("d", a);
}

static PyMethodDef methods[] = 
{
    {"wrapper_calc_area", wrapper_calc_area, METH_VARARGS, NULL},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef table = 
{
    PyModuleDef_HEAD_INIT,
    "samp", NULL, -1, methods
};

PyMODINIT_FUNC PyInit_samp(void)
{
    return PyModule_Create(&table);
}

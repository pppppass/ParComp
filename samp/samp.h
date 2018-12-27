#include <stdlib.h>

#ifndef PY_EXT
#include <stdio.h>
#include <time.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

#ifdef PY_EXT
#include <Python.h>
#endif

#include <omp.h>

void init_array(void);
int test_array(double x, double y);
int test_point(double x, double y, int it_min, int it_max);
double calc_area(double x_min, double x_max, double y_min, double y_max, int n_x, int n_y, int it_min, int it_max, int seed);

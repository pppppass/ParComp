#include "samp.h"

const double r_max = 2.0;

int test_point(double x, double y, int it_min, int it_max)
{
    if (test_array(x, y))
        return 0;
    double x_const = x, y_const = y;
    for (int i = 0; i < it_max; i++)
    {
        double x_temp = x;
        x = x * x - y * y + x_const;
        y = 2.0 * x_temp * y + y_const;
        if (x*x + y*y > r_max*r_max)
            return it_min <= i;
    }
    return 0;
}

double calc_area(double x_min, double x_max, double y_min, double y_max, int n_x, int n_y, int it_min, int it_max, int seed)
{
    double h_x = (x_max - x_min) / n_x, h_y = (y_max - y_min) / n_y;
    int ctr = 0;
#pragma omp parallel reduction(+:ctr)
#pragma omp for schedule(dynamic)
    for (int i = 0; i < n_x; i++)
    {
        srand48(seed + i);
        for (int j = 0; j < n_y; j++)
        {
            double x = x_min + h_x * i + h_x * drand48(), y = y_min + h_y * j + h_y * drand48();
            ctr += test_point(x, y, it_min, it_max);
        }
    }
    return (double)ctr / n_x / n_y * (x_max - x_min) * (y_max - y_min);
}

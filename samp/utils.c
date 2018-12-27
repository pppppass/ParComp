#include "samp.h"

const int l = 5;
const int p[5] = {1, 1, 2, 1, 3};
const int q[5] = {2, 3, 3, 4, 4};
const double eta[5] = {1.00, 0.97, 0.97, 0.98, 0.98};
double r[5];
double x_cen[5];
double y_cen[5];

void init_array()
{
    for (int i = 0; i < l; i++)
    {
        double theta = 2.0 * p[i] / q[i] * M_PI;
        r[i] = eta[i] * sin(M_PI * p[i] / q[i]) / q[i] / q[i];
        double x_tan = cos(theta) / 2.0 - cos(2.0 * theta) / 4.0, y_tan = sin(theta) / 2.0 - sin(2.0 * theta) / 4.0;
        double x_norm = cos(theta) - cos(2.0 * theta), y_norm = sin(theta) - sin(2.0 * theta);
        double r_norm = sqrt(x_norm*x_norm + y_norm * y_norm);
        x_cen[i] = x_tan + r[i] * x_norm / r_norm;
        y_cen[i] = y_tan + r[i] * y_norm / r_norm;
    }
    return ;
}

int test_array(double x, double y)
{
    double p = sqrt((x - 0.25)*(x - 0.25) + y*y);
    if (x <= p - 2.0 * p*p + 0.25)
        return 1;
    for (int i = 0; i < l; i++)
        if ((x - x_cen[i])*(x - x_cen[i]) + (y - y_cen[i])*(y - y_cen[i]) <= r[i]*r[i])
            return 1;
    return 0;
}

#include "samp/samp.h"

const int m = 10;

int main(int argc, const char* argv[])
{
    init_array();
    const int seed = 1;
    const double a_std = 1.5065918849;
    double m1, m2, t;
    m1 = 0, m2 = 0, t = 0;
    printf("Testing Multi-level 1024\n");
    for (int i = 0; i < m; i++)
    {
        double start = omp_get_wtime();
        double a = 9.0;
        a -= 2.0 * calc_area(-2.0, 1.0, 0.0, 1.5, 2048, 1024, 32768, 131072, seed);
        a -= 2.0 * calc_area(-2.0, 1.0, 0.0, 1.5, 4096, 2048, 8192, 32768, seed);
        a -= 2.0 * calc_area(-2.0, 1.0, 0.0, 1.5, 8192, 4096, 0, 8192, seed);
        printf("\tArea: %.20f\n", a);
        printf("\tError: %.20f\n", a - a_std);
        double end = omp_get_wtime();
        printf("\tTime: %.20f\n", end - start);
        m1 += a, m2 += a*a, t += end - start;
        
    }
    printf("Finished Multi-level 1024\n");
    m1 /= m, m2 /= m, t /= m;
    printf("Mean error: %.20f\n", m1 - a_std);
    printf("Standard deviation: %.20f\n", sqrt(m2 - m1*m1));
    printf("Average time: %.20f\n", t);
    m1 = 0, m2 = 0, t = 0;
    printf("Testing Multi-level 2048\n");
    for (int i = 0; i < m; i++)
    {
        double start = omp_get_wtime();
        double a = 9.0;
        a -= 2.0 * calc_area(-2.0, 1.0, 0.0, 1.5, 4096, 2048, 32768, 131072, seed);
        a -= 2.0 * calc_area(-2.0, 1.0, 0.0, 1.5, 8192, 4096, 8192, 32768, seed);
        a -= 2.0 * calc_area(-2.0, 1.0, 0.0, 1.5, 16384, 8192, 0, 8192, seed);
        printf("\tArea: %.20f\n", a);
        printf("\tError: %.20f\n", a - a_std);
        double end = omp_get_wtime();
        printf("\tTime: %.20f\n", end - start);
        m1 += a, m2 += a*a, t += end - start;
        
    }
    printf("Finished Multi-level 2048\n");
    m1 /= m, m2 /= m, t /= m;
    printf("Mean error: %.20f\n", m1 - a_std);
    printf("Standard deviation: %.20f\n", sqrt(m2 - m1*m1));
    printf("Average time: %.20f\n", t);
    return 0;
}

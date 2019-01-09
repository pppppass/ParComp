#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mat_mul.h"

// <<< |||
void swap_int(int* a, int* b)
{
  int t = *a;
  *a = *b;
  *b = t;
  return ;
}
// >>>

int main(int argc, char **argv){
  // <<<
  // int width = 512;  // default value
  // if (argc > 1) width = atoi(argv[1]); // user-specified value
  // printf("\nMatrix width: %d.\n", width);
  // |||
  if (argc != 4 && argc != 5)
    return 1;
  int width, dummy, height, width_old;
  sscanf(argv[1], "%d", &height);
  sscanf(argv[2], "%d", &dummy);
  sscanf(argv[3], "%d", &width);
  if (argc == 5)
  {
    sscanf(argv[4], "%d", &width_old);
    printf("Size: (old) %d * %d * %d, (new) %d * %d * %d\n", height, dummy, width, width_old, width_old, width_old);
  }
  else
  {
    width_old = -1;
    printf("Size: (new) %d * %d * %d\n", height, dummy, width);
  }
  // >>>

  // <<< |||
  if (width_old > 0)
  {
    swap_int(&width, &width_old);
  // >>>

    srand(time(NULL));
    float* M = rand_mat(width, width);
    float* N = rand_mat(width, width);

    float* cpu_P = raw_mat(width, width);
    float* gpu_P = raw_mat(width, width);

    long long cpu_start_time = start_timer();
    cpu_mat_mul(M, N, cpu_P, width);
    // <<<
    // long long cpu_time = stop_timer(cpu_start_time, "CPU");
    // |||
    long long cpu_time = stop_timer(cpu_start_time, "CPU (old)");
    // >>>

    long long gpu_start_time = start_timer();
    gpu_mat_mul(M, N, gpu_P, width);
    // <<<
    // long long gpu_time = stop_timer(gpu_start_time, "GPU");
    // |||
    long long gpu_time = stop_timer(gpu_start_time, "GPU (old)");
    // >>>

    // <<< |||
    gpu_start_time = start_timer();
    gpu_mat_mul(M, N, gpu_P, width);
    gpu_time = stop_timer(gpu_start_time, "GPU (old, repeat)");
    // >>>

    // Check the correctness of the GPU results
    int num_wrong = 0;
    for (int i = 0; i < width * width; i++) {
      if (fabs(cpu_P[i] - gpu_P[i]) > 0.000001) num_wrong++;
    }
    
    // Report the correctness results
    // <<<
    // if (num_wrong) printf("GPU %d / %d values incorrect\n", num_wrong, N);
    // else           printf("GPU all values correct\n");
    // |||
    if (num_wrong) printf("GPU (old) %d / %d values incorrect\n", num_wrong, width*width);
    else           printf("GPU (old) all values correct\n");
    // >>>

  // <<< |||
    swap_int(&width, &width_old);
  }
  // >>>
  
  // <<< |||
    float* M_new = rand_mat(height, dummy);
    float* N_new = rand_mat(dummy, width);

    float* cpu_P_new = raw_mat(height, width);
    float* gpu_P_new = raw_mat(height, width);

    long long cpu_start_time_new = start_timer();
    cpu_mat_mul_new(M_new, N_new, cpu_P_new, height, dummy, width);
    long long cpu_time_new = stop_timer(cpu_start_time_new, "CPU (new)");

    long long gpu_start_time_new = start_timer();
    gpu_mat_mul_new(M_new, N_new, gpu_P_new, height, dummy, width);
    long long gpu_time_new = stop_timer(gpu_start_time_new, "GPU (new)");

    gpu_start_time_new = start_timer();
    gpu_mat_mul_new(M_new, N_new, gpu_P_new, height, dummy, width);
    gpu_time_new = stop_timer(gpu_start_time_new, "GPU (new, repeat)");

    // for (int i = 0; i < 100; i++)
    //   printf("%d %lf %lf \n", i, cpu_P_new[i], gpu_P_new[i]);

    int num_wrong_new = 0;
    for (int i = 0; i < height*width; i++) {
      if (fabs(cpu_P_new[i] - gpu_P_new[i]) > 0.000001) num_wrong_new++;
    }
    
    if (num_wrong_new) printf("GPU (new) %d / %d values incorrect\n", num_wrong_new, height*width);
    else           printf("GPU (new) all values correct\n");
  // >>>
}

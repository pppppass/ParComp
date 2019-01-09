#include<cuda.h>
#include<stdio.h>
#include<math.h>

#define TILE_WIDTH 16 

extern "C" void gpu_mat_mul(float* h_M, float* h_N, float* h_P, int width);
// <<< |||
extern "C" void gpu_mat_mul_new(float* h_M, float* h_N, float* h_P, int height, int dummy, int width);
// >>>

__global__
void gpu_mat_mul_kernel(float* M, float* N, float* P, int width) {
  __shared__ float Mds[TILE_WIDTH][TILE_WIDTH];
  __shared__ float Nds[TILE_WIDTH][TILE_WIDTH];

  int bx = blockIdx.x; 
  int by = blockIdx.y;
  int tx = threadIdx.x;
  int ty = threadIdx.y;

  // Identify the row and column of the P element to work on
  // Each thread works on an element of P
  int Row = by * TILE_WIDTH + ty;
  int Col = bx * TILE_WIDTH + tx;

  int phase_num = ceil(width / (float)TILE_WIDTH);
  float Pvalue = 0;
  // Each thread loads 'Row'th row of M and 'Col'th column of N
  for (int ph = 0; ph < phase_num; ++ph) {
        
    Mds[ty][tx] = M[Row * width + ph * TILE_WIDTH + tx];   
    Nds[ty][tx] = N[(ph * TILE_WIDTH + ty) * width + Col];

    __syncthreads();

    for (int k = 0; k < TILE_WIDTH; ++k) { 
      Pvalue += Mds[ty][k] * Nds[k][tx];
    }

    __syncthreads();
  }

  P[Row * width + Col] = Pvalue;
}

// <<< |||
__global__
void gpu_mat_mul_kernel_new(float* M, float* N, float* P, int height, int dummy, int width) {
  __shared__ float Mds[TILE_WIDTH][TILE_WIDTH];
  __shared__ float Nds[TILE_WIDTH][TILE_WIDTH];

  int bx = blockIdx.x;
  int by = blockIdx.y;
  int tx = threadIdx.x;
  int ty = threadIdx.y;

  int Row = bx * TILE_WIDTH + tx;
  int Col = by * TILE_WIDTH + ty;

  int phase_num = ceil(dummy / (float)TILE_WIDTH);
  float Pvalue = 0.0;

  for (int ph = 0; ph < phase_num; ++ph) {

    if (Row < height && ph * TILE_WIDTH + ty < dummy)
      Mds[tx][ty] = M[Row * dummy + ph * TILE_WIDTH + ty];
    if (Col < width && ph * TILE_WIDTH + tx < dummy)
      Nds[tx][ty] = N[(ph * TILE_WIDTH + tx) * width + Col];

    __syncthreads();
    
    for (int k = 0; k < TILE_WIDTH; ++k)
      if (ph * TILE_WIDTH + k < dummy)
        Pvalue += Mds[tx][k] * Nds[k][ty];

    __syncthreads();

    if (Row < height && Col < width)
      P[Row * width + Col] = Pvalue;
  }
}
// >>>

void gpu_mat_mul(float* h_M, float* h_N, float* h_P, int width) {
  float *d_M, *d_N, *d_P;

  size_t size_of_float = sizeof(float);
  size_t size_M = width * width * size_of_float;
  size_t size_N = width * width * size_of_float;
  size_t size_P = width * width * size_of_float;

  cudaMalloc((void**)&d_M, size_M);
  cudaMalloc((void**)&d_N, size_N);
  cudaMalloc((void**)&d_P, size_P);
    
  cudaMemcpy(d_M, h_M, size_M, cudaMemcpyHostToDevice);
  cudaMemcpy(d_N, h_N, size_N, cudaMemcpyHostToDevice);

  cudaEvent_t start, stop;
  float elapsed_time = 0.0;
  cudaEventCreate(&start);
  cudaEventCreate(&stop);
  cudaEventRecord(start, 0);

  dim3 grid_dim(ceil(width / (float)(TILE_WIDTH)), ceil(width / (float)(TILE_WIDTH)), 1);
  dim3 block_dim(TILE_WIDTH, TILE_WIDTH,1);
  gpu_mat_mul_kernel<<<grid_dim, block_dim>>>(d_M, d_N, d_P, width);

  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);

  cudaMemcpy(h_P, d_P, size_P, cudaMemcpyDeviceToHost);
    
  // Free device memory for M, N, P
  cudaFree(d_M);
  cudaFree(d_N);
  cudaFree(d_P);

  cudaEventElapsedTime(&elapsed_time, start, stop);
  printf("  grid  dim:  %d, %d, %d.\n", grid_dim.x, grid_dim.y, grid_dim.z);
  printf("  block dim: %d, %d, %d.\n", block_dim.x, block_dim.y, block_dim.z);
  printf("  kernel time: %.5f sec\n", elapsed_time / 1000);

  cudaEventDestroy(start);
  cudaEventDestroy(stop);
}

// <<< |||
void gpu_mat_mul_new(float* h_M, float* h_N, float* h_P, int height, int dummy, int width) {
  float *d_M, *d_N, *d_P;

  size_t size_of_float = sizeof(float);
  size_t size_M = height * dummy * size_of_float;
  size_t size_N = dummy * width * size_of_float;
  size_t size_P = height * width * size_of_float;

  cudaMalloc((void**)&d_M, size_M);
  cudaMalloc((void**)&d_N, size_N);
  cudaMalloc((void**)&d_P, size_P);
    
  cudaMemcpy(d_M, h_M, size_M, cudaMemcpyHostToDevice);
  cudaMemcpy(d_N, h_N, size_N, cudaMemcpyHostToDevice);

  cudaEvent_t start, stop;
  float elapsed_time = 0.0;
  cudaEventCreate(&start);
  cudaEventCreate(&stop);
  cudaEventRecord(start, 0);

  dim3 grid_dim(ceil(height / (float)(TILE_WIDTH)), ceil(width / (float)(TILE_WIDTH)), 1);
  dim3 block_dim(TILE_WIDTH, TILE_WIDTH,1);
  gpu_mat_mul_kernel_new<<<grid_dim, block_dim>>>(d_M, d_N, d_P, height, dummy, width);

  cudaEventRecord(stop, 0);
  cudaEventSynchronize(stop);

  cudaMemcpy(h_P, d_P, size_P, cudaMemcpyDeviceToHost);
    
  cudaFree(d_M);
  cudaFree(d_N);
  cudaFree(d_P);

  cudaEventElapsedTime(&elapsed_time, start, stop);
  printf("  grid  dim:  %d, %d, %d.\n", grid_dim.x, grid_dim.y, grid_dim.z);
  printf("  block dim: %d, %d, %d.\n", block_dim.x, block_dim.y, block_dim.z);
  printf("  kernel time: %.5f sec\n", elapsed_time / 1000);

  cudaEventDestroy(start);
  cudaEventDestroy(stop);
}
/// >>>

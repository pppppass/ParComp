void cpu_mat_mul(float* M, float* N, float* P, int width) {
  for(int i = 0; i < width; i++) {
    for(int j = 0; j < width; j++) {
      float sum = 0.0;
      for(int k = 0; k < width; k++) {
        sum += M[i * width + k] * N[k * width + j];
      }
      P[i * width + j] = sum;
    }
  }
}

// <<< |||
void cpu_mat_mul_new(float* M, float* N, float* P, int height, int dummy, int width) {
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      float sum = 0.0;
      for(int k = 0; k < dummy; k++) {
        sum += M[i * dummy + k] * N[k * width + j];
      }
      P[i * width + j] = sum;
    }
  }
}
// >>>

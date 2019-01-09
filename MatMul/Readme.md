# Matrix Multiplication Using CUDA

This is the second assignment of the course.

## Organization

The files are organized as follows:
1. `mat_mul.*` Source codes (modified according to the requirement).

## Usage

The current wording directory is assumed in the the folder `MatMul`.

To reproduce the final numerical results for benchmarking:
1. Ensure the environment has `cuda=9.0`.
2. Execute `make bench` to reproduce the result;
3. The numerical results are placed in `job_ID_gpu0x.out`, say `job_7154_gpu02.out`.

## Interface

We use command line arguments to specify the size of matrices.
1. `mat_mul height dummy width`: Test P = M N where M is of `height` * `dummy` and N is of `dummy` * `width`, using the modified algorithm which handles boundaries.
2. `mat_mul height dummy width width_old`: Test both 1 using the modified algorithm (new) and P = M N where M and N are both of `width_old` * `width_old` using the original algorithm (provided in `cuda-ex5`), for comparison.

## Results

We may directly observe numerical results in `job_7154_gpu02.out`. When `height`, `dummy` and `width` are identical multiplicative of `TILE_SIZE`, the modified algorithm yields a correct result and the efficiency is slightly slower than the original algorithm (compare lines starting with `GPU (old, repeat)` and `GPU (new, repeat)`) since more details need to be handled. When `height`, `dummy` and `width` are different values or is not a multiplicative of `TILE_SIZE`, the modified algorithm also yields a correct result.

We notice that if we repeat the calculation using GPU, the second calculation is generally much faster than the first one. This may be caused by caching issues of GPU.



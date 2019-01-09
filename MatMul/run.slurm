#!/bin/bash

#SBATCH -o job_%j_%N.out
#SBATCH --partition=gpu
#SBATCH -J mat_mul 
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --gres=gpu:1
#SBATCH -t 10:00

./mat_mul 128 128 128 128
./mat_mul 256 256 256 256
./mat_mul 512 512 512 512
./mat_mul 1024 1024 1024 1024

./mat_mul 1 1 1
./mat_mul 17 18 19
./mat_mul 87 512 512
./mat_mul 3 204 1892
./mat_mul 1023 1024 1025
./mat_mul 512 769 1024
./mat_mul 1027 1031 1035

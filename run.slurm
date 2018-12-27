#!/bin/bash

#SBATCH -o job_%j_%N.out
#SBATCH --partition=cpu
#SBATCH -J Mandelbrot
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=8
#SBATCH --cpus-per-task=1
#SBATCH -t 10:00

./Main

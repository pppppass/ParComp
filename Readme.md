# Assignments for Foundations of Parallel and Distributive Computing

## Introduction

This is the repository of assignments of the course *Foundations of Parallel and Distributive Computing* lectured by *Chao Yang* in Fall 2018. The author of this repository is [Zhihan Li](mailto:lzh2016p@pku.edu.cn).

This repository relies on the personal TeX templates package [ptmpls](https://github.com/pppppass/ptmpls). Remember to specify `--recursive` option when cloning the repository.

Since there is one single assignment, namely calculation of the area of the Mandelbrot set, the files are directly placed in the root folder.

## Organization

The files are organized as follows:
1. `ptmpls`: Personal TeX / LaTeX templates;
2. `samp`: C-based Monte Carlo sampler;
    1. `samp/samplers.c`: Main sampler for the area of Mandelbrot set;
    2. `samp/utils.c`: Helper procedures, mainly for fast checking;
    3. `samp/wrappers.c`: Wrappers for Python;
3. `Main.c`: Main driver to run the sampler, for final benchmarking.
5. `Problem.py`: Python script to perform numerical experiments, for figures and tables.

## Environment

The numerical results are all produced in a specific environment. The hardware configuration can be found in `hardware.txt`. An Anaconda environment is set up according to `environment.yml`.

## Usage

There are Makefiles distributed in folders.

To compile reports:
1. Install TeX Live or other TeX utilities with LuaLaTeX and ensure that they can be found by `PATH`;
2. Execute `make` or `make report` in the root folder to recursively compile all reports;
3. The report is `Report.pdf`.

To reproduce the figures and tables:
1. Activate Anaconda and execute `make environment` in the root folder to create a new environment `parcomp`;
2. Activate the environment `parcomp`;
3. Execute `make run` to generate the figures and tables;
4. The figures and tables are updated;
4. By `make` or `make report` again, the numerical results are updated in the report, say `Report.pdf`.

To reproduce the final numerical results for benchmarking:
1. Activate Anaconda and execute `make environment` in the root folder to create a new environment `parcomp` and activate the environment `parcomp`, or ensure the environment has **gcc>=8.2.0**;
2. Execute `make bench` to reproduce the result;
3. The numerical results are placed in `job_ID_cu0x.out`, say `job_4479_cu01.out`.

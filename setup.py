from distutils.core import setup, Extension
import numpy

samp = Extension("samp", sources=["samp/samplers.c", "samp/utils.c", "samp/wrappers.c"], include_dirs=[numpy.get_include()], libraries=["mkl_rt"], extra_compile_args=["-fopenmp", "-DPY_EXT"], extra_link_args=["-fopenmp"])

setup(ext_modules=[samp])

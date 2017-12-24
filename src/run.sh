#!/bin/bash

mpicc origin.c -lpnetcdf -lm
mpirun -n 1 ./a.out
rm a.out

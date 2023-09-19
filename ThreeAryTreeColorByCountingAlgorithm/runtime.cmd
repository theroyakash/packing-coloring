#!/bin/bash 
#PBS -o logfile.log
#PBS -e errorfile.err
#PBS -l walltime=02:00:00
#PBS -l select=1:ncpus=32

make
./main
make clean
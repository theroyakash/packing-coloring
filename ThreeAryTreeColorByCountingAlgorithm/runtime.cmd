#!/bin/bash 
#PBS -o logf.log
#PBS -e errf.err
#PBS -l walltime=20:00:00
#PBS -l select=1:ncpus=32

cd ./ThreeAryTreeColorByCountingAlgorithm
make
./main
make clean
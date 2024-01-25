#!/bin/bash 
#PBS -o logf.log
#PBS -e errf.err
#PBS -l walltime=20:00:00
#PBS -l select=1:ncpus=32

tpdir=`echo $PBS_JOBID | cut -f 1 -d .` 
tempdir=$HOME/scratch/job$tpdir 
mkdir -p $tempdir 
cd $tempdir 
cp -R $PBS_O_WORKDIR/* .

make
./main
make clean

mv ../job$tpdir $PBS_O_WORKDIR/.
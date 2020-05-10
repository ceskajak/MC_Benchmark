#!/bin/bash
#PBS -l nodes=1:ppn=1
#PBS -e ./error000000

cd /home/ceskajak/Benchmark/new/PYTHIA_seeds
source /data2/vyuka/ssd/setup_ROOT6.08.06.sh
source /home/ceskajak/scripts/setup_Pythia8244.sh
./RunPythia000000

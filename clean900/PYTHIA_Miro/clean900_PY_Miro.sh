#!/bin/bash
#PBS -l nodes=1:ppn=1
#PBS -e ./error

cd /home/ceskajak/Benchmark/clean900/PYTHIA_Miro
source /data2/vyuka/ssd/setup_ROOT6.08.06.sh
source /home/ceskajak/scripts/setup_Pythia8244.sh
./RunPythia 

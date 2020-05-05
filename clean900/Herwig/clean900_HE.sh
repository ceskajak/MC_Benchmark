#!/bin/bash
#PBS -l nodes=1:ppn=1
#PBS -e ./error00
cd /home/ceskajak/Benchmark/clean900/Herwig
source /data2/vyuka/ssd/setup_ROOT6.08.06.sh
source /data2/vyuka/ssd/Programs/Herwig-7.1.2-root6.08/bin/activate
Herwig run LHC_MB_all.run -N 1000000 -s 125442

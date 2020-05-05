#!/bin/bash

for i in {5..15..1}
do
	cd ./PYTHIA_Miro_tau$i
	qsub -q normal *.sh
	cd ..
done

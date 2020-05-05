#!/bin/bash

for i in {5..15..1}
do
	mkdir "PYTHIA_Miro_tau$i"
	cp ./original/MinBias.cc PYTHIA_Miro_tau$i
	cp ./original/clean500_PY_Miro_tauREPLACE.sh PYTHIA_Miro_tau$i/clean500_PY_Miro_tau$i.sh
	cd PYTHIA_Miro_tau$i
	sed -i "s/REPLACE/$i/g" *
	/home/ceskajak/scripts/compile.sh
	cd ..
	
	echo tau$i generated
done

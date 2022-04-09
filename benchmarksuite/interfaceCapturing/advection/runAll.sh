#!/bin/sh
cd ${0%/*} || exit 1    # Run from this directory

./discUniFlow/runAll.sh
./discUniFlowTet/runAll.sh
./vortexShearedDisc/runAll.sh
./vortexShearedDiscTet/runAll.sh
#./deformationSphere/runAll.sh
./Leveque/runAll.sh
./LevequeTet/runAll.sh
./deformationSphereTet/runAll.sh
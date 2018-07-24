#!/bin/sh

#for loop (execute ./unpacking.sh 7)
if [ $# != 1 ]; then
    echo "usage: $0 MAX" 1>&2
    exit 0
fi

MAX=$1

i=0
while [ $i -le $MAX ]; do
    ./TDMunpack -f ../../../data/2018_Mar_May/7Apr_1/7Apr_1_MCR"$i"_T2K_beamline_trigger_beam60us_neutrinos_ON.daq  1>&2
    i=`expr $i + 1`
done

   
ls -1 ../../../data/2018_Mar_May/7Apr_1/*Slot* > febs_files_list.list
./unpack -f d
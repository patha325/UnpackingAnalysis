#!/bin/sh

#for loop (execute ./unpacking.sh 7)

if [ $# != 3 ]; then
    echo "usage: $0 date month run" 1>&2
    exit 0
fi

MAX=7

i=0
date=$1
run=$2
mon="$3"
while [ $i -le $MAX ]; do
    ../Decorder/Unpacking_3.2/bin/TDMunpack -f ~/data/"$date"May_"$run"_ON_MCR"$i"_T2K_beamline_trigger_beam60us_neutrinos_ON.daq  1>&2
    i=`expr $i + 1`
done

   
#ls -1 /Users/jinaren/Documents/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/data/2018_Mar_May/11Apr_5/*Slot* > ../Decorder_temp/bin/febs_files_list.list
#../Decorder_temp/bin/unpack -f d
cd ../Decorder/Unpacking_3.2/bin
ls -1 ~/data/*Slot* > febs_files_list.list
./unpack -f d

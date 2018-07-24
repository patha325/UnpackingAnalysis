#!/bin/sh

cd ../Analysis
i=1
j=1
k=1
n=2
N=30
NN=10
analysis="a"
DataDir="/Users/jinaren/Documents/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/Recon"
while [ $k -le $n ]
 do
    if [ $k -eq 1 ]
    then
        mon="mar"
    elif [ $k -eq 2 ]
    then
        mon="Apr"
    else
        mon="May"
    fi
    i=1
        while [ $i -le $N ]
        do
            j=1
            while [ $j -le $NN ]
            do
                echo " $i $j $mon "
                if [ -e $DataDir/"Recon_"$i"_"$mon"_"$j".root" ]
                then
                    echo "There is a directory, Recon_$i"_"$mon"_"$j.root."
                    ./recon $i $j $mon $analysis
                else
                    echo " There is not a directory, Recon_$i"_"$mon"_"$j.root"
                    break
                fi
		                j=$(( j+1 ))
            done
            echo " $i $j $mon"
    #if (-f $DataDir/$i$mon _ $j)                                               
            i=$(( i+1 ))
        done
        k=$(( k+1 ))
done


#!/bin/sh

cd ../Analysis
i=1
j=1
k=1
n=2
N=30
NN=10
DataDir="/Users/jinaren/Documents/T2K/BabyMIND/commissioning_run/event_estimation/macro/Myanalysis/data/2018_Mar_May"
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
		if [ -e $DataDir/$i$mon"_"$j ]  
		then
		    echo "There is a directory, $i$mon"_"$j."
		    ./decorder $i $j $mon
		else
		    echo " There is not a directory, $i$mon"_"$j."
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



#!/bin/sh

if [ $# != 3 ]; then
    echo "usage: $0 date run month" 1>&2
    exit 0
fi

date=$1
run=$2
mon="$3"

mkdir ../Image/Eventdisp_"$date"_"$mon"_"$run"

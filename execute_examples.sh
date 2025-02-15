#!/bin/bash

# Initial time
current_date=$(date +%m-%d-%Y)
current_time=$(date | awk '{print $4}')
echo ${current_date}
echo ${current_time}
echo "Start = Start time"
current_start=$current_date@:$current_time


# Global variables
target_name=$1


# Compilation process
if [ ! -d build ]; then
    mkdir build
fi
cd build/
cmake -S ../ -B .
cmake --build . --target $target_name
cd ../


# Check the execution target is right
if [ "${target_name}" != "graphAlgorithms" ]; then
    echo "Target name wrong. Remid the option is graphAlgorithms."
    exit 127
fi


# Excution process
if [ "${target_name}" == "graphAlgorithms" ]; then
    echo "time ./build/graphAlgorithms"
    time ./build/graphAlgorithms
    rm ./build/graphAlgorithms
fi


# Finish time
current_date=$(date +%m-%d-%Y)
current_time=$(date | awk '{print $4}')
echo "Finish = Finish"
echo ${current_date}
echo ${current_time}
current_finish=$current_date@:$current_time

# Difftime
date2sec() { date -d "$(sed 's|-|/|g; s|@| |; s|:| |' <<<"$*")" +%s; }
second=$(echo $(( $(date2sec "$current_finish") - $(date2sec "$current_start") )))
echo "Your bash script needs $second seconds to process"

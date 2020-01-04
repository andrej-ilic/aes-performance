#!/bin/bash

echo "Compiling..."
gcc keygen.c -o keygen
gcc payload.c -o payload
gcc aes.c -o aes
nvcc aes.cu -o aescuda > /dev/null

echo "Running..."

./keygen

rm results.csv 2> /dev/null
rm resultsCUDA.csv 2> /dev/null

echo "n,seconds" >> results.csv
echo "n,milliseconds" >> resultsCUDA.csv

for i in `seq 14 26`
do
	size=`./payload $i | cut -d ' ' -f5`
	echo "Encrypting payload of size $size"
	time=`{ time ./aes; } 2>&1 | grep real | awk '{print $2}'`
	time="${time//0m}"
	time="${time//s}"
	timeCUDA=$(./aescuda | tail -1)
	echo "$i,$time" >> results.csv
	echo "$i,$timeCUDA" >> resultsCUDA.csv
done

rm key.txt payload.txt out.txt outcuda.txt

echo "Output: results.csv"
echo "Output: resultsCUDA.csv"

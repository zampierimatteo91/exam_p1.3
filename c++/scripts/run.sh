#!/bin/bash

make

#remove existing data--------
touch data.txt
rm data.txt

#run-------------------------
for size in 100 1000 10000 100000
do
		touch tmp${size}.txt
		rm tmp${size}.txt

		for runs in $(seq 1 10)
		do
		./test_find.x ${size} >> tmp.txt
		done
		awk -v N=${size} 'BEGIN {sum1=0; sum2=0; sum3=0} 1 {sum1=sum1+$2; sum2=sum2+$3; sum3=sum3+$4} END {print N, sum1/10, sum2/10, sum3/10}' tmp.txt 1>> data.txt

		rm tmp.txt
		
done

make clean
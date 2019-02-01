#!/bin/bash

cd ../

make

#remove existing data--------
touch test.txt
rm test.txt

#run-------------------------
for size in 1000 5000 10000 25000 50000 75000 100000
do
		touch tmp${size}.raw
		rm tmp${size}.raw

		for runs in $(seq 1 10)
		do
		./test_find.x ${size} | head -1 >> tmp.raw
		done
		awk -v N=${size} 'BEGIN {sum1=0; sum2=0; sum3=0} 1 {sum1=sum1+$2; sum2=sum2+$3; sum3=sum3+$4} END {print N, sum1/10, sum2/10, sum3/10}' tmp.raw 1>> test.txt

		rm tmp.raw
		
done

make clean
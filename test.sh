#!/bin/bash
echo 5,5 AGAINST aggressive.py >> log55.txt
while read line; do
  echo $line
done < file.txt

tail -1 log12.txt | head -1 

for i in aggressive.py defensive.py third.py ./run.sh Randomplayer.py
do
	echo $i
done

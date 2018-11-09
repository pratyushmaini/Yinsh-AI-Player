#!/bin/bash
echo 5,5 AGAINST  >> log.txt
python server.py 10000 -n 5 -s 5 -NC 2 -TL 120 -LOG server.log &
python client.py 0.0.0.0 10000 ./run.sh &
python client.py 0.0.0.0 10000 aggressive.py -mode GUI 
pkill -9 python

python server.py 10000 -n 6 -s 5 -NC 2 -TL 150 -LOG server.log &
python client.py 0.0.0.0 10000 ./run.sh &
python client.py 0.0.0.0 10000 aggressive.py -mode GUI 
pkill -9 python

python server.py 10000 -n 6 -s 6 -NC 2 -TL 180 -LOG server.log &
python client.py 0.0.0.0 10000 ./run.sh &
python client.py 0.0.0.0 10000 aggressive.py -mode GUI 
pkill -9 python

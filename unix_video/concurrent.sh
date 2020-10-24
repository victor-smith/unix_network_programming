#!/bin/bash

for (( i=1; i<655360; i++ ))
do

nc 127.0.0.1 6666 < info.txt &  

done

echo "DONE"

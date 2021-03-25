#!/bin/bash

# Prompt user 

echo "Input the dictionary and grid file, in that order, when prompted \n"

# Read in info

read -p "Dictionary file: " dict
read -p "Grid file: " grid

# Get Running time 

TOTAL=0
RUNNING_TIME=`./a.out $dict $grid | tail -1`
TOTAL=$((TOTAL+RUNNING_TIME))
RUNNING_TIME=`./a.out $dict $grid | tail -1`
TOTAL=$((TOTAL+RUNNING_TIME))
RUNNING_TIME=`./a.out $dict $grid | tail -1`
TOTAL=$((TOTAL+RUNNING_TIME))
RUNNING_TIME=`./a.out $dict $grid | tail -1`
TOTAL=$((TOTAL+RUNNING_TIME))
RUNNING_TIME=`./a.out $dict $grid | tail -1`
TOTAL=$((TOTAL+RUNNING_TIME))
AVERAGE=$((TOTAL/5))

echo "Average running time: $AVERAGE ms"

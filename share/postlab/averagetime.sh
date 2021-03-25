#!/bin/bash

# Prompt user 
# Read in info

I=0
echo "enter the exponent for counter.cpp: " 
read -p "" ITERATIONS
# Check if input was quit

if [ "$ITERATIONS" == "quit" ] 
then
	exit
fi 
# Get Running time 

# Declare the total running time variable and the average
TOTAL=0
AVERAGE=0

while [ $I -lt 5 ]; do 
	# Run counter.cpp with iterations as input
	RUNNING_TIME=`./a.out $ITERATIONS`
	# Echo that message
	echo "Running iteration $(($I+1))..."
	echo "time taken: $RUNNING_TIME ms"
	TOTAL=$(($TOTAL + $RUNNING_TIME))
	#Increment i
	I=$(($I+1))
done

AVERAGE=$(($TOTAL/5))

echo "$I iterations took $TOTAL ms"
echo "Average time was: $AVERAGE ms"
#!/bin/bash

if [ $# -eq 2 ]
then
	filesdr=$1
	searchstr=$2

	if [ -d $filesdr ]
	then
		files_num=$(find $filesdr -type f | wc -l)
		matches=$(grep -r "$searchstr" $filesdr | wc -l)
		echo "The number of files are $files_num and the number of matching lines are $matches"
	else
		echo "$filesdr does not exist"
		exit 1 
	fi
else
	echo "Check your paramenters"
	exit 1
fi
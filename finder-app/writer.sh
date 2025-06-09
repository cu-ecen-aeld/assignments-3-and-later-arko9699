#!/bin/bash

if [ $# -eq 2 ]
then
	destination=$1
	writestring=$2
	dirname="$(dirname "${destination}")"

	mkdir -p $dirname
	echo "$writestring" > $destination
	exit $?
else
	echo "Not the correct number of parameters"
	exit 1
fi
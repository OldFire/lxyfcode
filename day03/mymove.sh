#!/bin/bash
files=$(find $1 -size +100M -type f)
##############echo $files
mkdir $2 -p
dst=$2"/"
###############echo $dst
for var in $files;do
	 mv $var $dst
done


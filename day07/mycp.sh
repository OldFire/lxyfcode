#!/bin/bash
files=$(find $1 -type f|grep -E '\.cpp$|\.sh$|\.c$|\.sql$')
##############echo $files
mkdir $2 -p
dst=$2"/"
###############echo $dst
for var in $files;do
	 cp $var $dst
done


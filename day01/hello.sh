#!/bin/bash
echo "hello world"
var1=abc
var2=abc
if [ $var1 = $var2 ]
then
	echo "var2 equal var1"
fi


var="a b c d"
for v in $var
do
	echo $v
done


var=100
printf "%d\n" $var

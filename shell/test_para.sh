#!/bin/bash

function show_help()
{
	echo 'help'
}

aa=dddd

line1=`wc -l ./i1 | awk '{print $1}'`
line2=`wc -l ./i2 | awk '{print $1}'` 

if [ ! ${line1} -eq ${line2} ] ; then
	echo 'equation'
	else
		echo  ${line1}'not equation'
fi

echo $line1
echo $line2

echo $aa

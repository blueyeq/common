#!/bin/bash

find_str='default str'

function str_file()
{

	for file in $( ls ./ ) ; do
#		echo $file
		if [ -d $file ] ; then 
			cd $file 
			str_file
		else 
			cat $file | grep ${find_str}| while read line ; do echo $file $line; done
		fi
	done
cd ../
}

str_file

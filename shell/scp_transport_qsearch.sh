#!/bin/bash

test_case=1
dirname='env'
srcdir=./bin
dest=i01.qsst.zzbc:/home/s/qiurunli/$dirname$test_case/common/bin

echo 'destion:[' ${dest} ']'
echo 'srcdir:[' ${srcdir} ']'
#transport files
tran_files='qfedTool
			qfedd
		   '
#			qnetd
#			qnetinfo
#			qsrchd          
#			qsrchTool       
#			qsumd           
#			wordJoin
			
#			qbuild_reader 
#			print_ucs2 
#			print_word_id  
#			qindex_reader  
#			query_analyzer 
#			random 
#			stroage_reader 
#			syncheck 
#			trans_to_json


# transport by search
for file in $tran_files; do
	scp ${srcdir}/${file} ${dest}/${file}.qrl 	
	if [ $? -eq 0 ] ; then
		echo $dest/${file}' transport success'
		else   echo $dest/${file} 'transport failed'
	fi
done



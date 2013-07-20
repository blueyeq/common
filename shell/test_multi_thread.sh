#!/bin/bash

files=`ls ./`
thread=10
echo $1
sum_lines=`wc -l $1 | awk '{print $1}'`
file_lines=$((${sum_lines}/${thread}))

if [ ${lines} -eq 0 ] ; then
	file_lines=${sum_lines}
fi

echo ${sum_lines}, ${file_lines}


split -d -a 5 -l ${file_lines} $1 



files=`ls ./ | grep '[0-9][0-9][0-9][0-9][0-9]' `

for file in ${files}
do 
	echo ${file}
	wc -l ${file}
done


for ((i=0; $i < 10; i=$(($i+1)))) 

do
{
	sleep 1
	echo $i;
}&
done

wait



echo 'done'
echo $$


for file in ${files}
do 
	rm -f ${file}
done

ps -ef | grep test_mu

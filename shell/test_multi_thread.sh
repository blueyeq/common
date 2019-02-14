#!/bin/bash

files=`ls ./`
thread=5
echo $1
sum_lines=`wc -l $1 | awk '{print $1}'`
file_lines=$((${sum_lines}/${thread}))
with_head=true

if [[ ${file_lines} -eq 0 ]] ; then
	file_lines=${sum_lines}
fi

echo ${sum_lines}, ${file_lines} ${thread}

split -d -a 5 -l ${file_lines} $1 



files=`ls ./ | grep '[0-9][0-9][0-9][0-9][0-9]' `

for file in ${files}
do 
{
	echo ${file}
        if [[ ${with_head} ]]
        then
            head -1 $1 >${file}.tmp
            cat ${file} >>${file}.tmp
            mv ${file}.tmp ${file}
        fi
	wc -l ${file}
        python call_pricing.py ${file} >${file}.out
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

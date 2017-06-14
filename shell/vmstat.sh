#!/bin/bash

predays=''

for((i=1;i>0;++i))
do
	date +%m%d%H%M%S
	day=`date +%m%d`
	if [[ "${day}" != "${lastday}" ]]
	then
		file=vm.${day}
		if [[ "${lastlastday}" != "" ]]
		then
			rm ${lastlastday}
		fi
		lastdayday=${lastday}
		lastday=${day}
		touch ${file}
	fi
	if [[ ! -f ${file} ]]
	then
		touch ${file}
	fi

	vmstate 1 1000 >>${file}
done

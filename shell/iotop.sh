#!/bin/bash

PREFIX=iolog
CMD="iotop -n 1200 -Pobd 1"
STARTHM=2350
predays=('day1' 'day2' 'day4')
size=${#predays[@]}


for((i=1;i>0;++i))
do
	date=`date +%m%d%H%M%S`
	day=`date +%m%d`
	hm=`date +%H%M`
	if [[ "${hm}" != "${STARTHM}" ]]
	then
		sleep 1
		continue
	fi

	if [[ "${day}" != "${predays[0]}" ]]
	then
		file=${PREFIX}.${day}
#echo 'new file:' ${file}
		if [[ "${predays[$((${size}-1))]}" != "" ]]
		then
			del=${PREFIX}.${predays[$((${size}-1))]}
#			echo 'del: ' ${del}
			[[ -f ${del} ]] && rm -f ${del}
		fi

		for((i=$((${size}-1)); i>0; i--))
		do
			predays[$i]=${predays[$(($i-1))]}
	    done
		predays[0]=${day}
		
		touch ${file}
	fi

	[[ -f ${file} ]]  || touch ${file}

	echo ${date} >>${file}
	${CMD} >>${file}
done

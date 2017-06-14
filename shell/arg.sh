#!/bin/bash
#./arg.sh -a 3 -b 4

function usage()
{
	echo 'a:b:h'
}


while getopts a:b:h opt
do
	case ${opt} in
		a)
			echo 'a' ${OPTARG}
			;;
		b)
			echo 'b' ${OPTARG}
			;;
		?)
			echo 'unknow ' ${opt} ${OPTARG}
			usage
			;;
	esac
done

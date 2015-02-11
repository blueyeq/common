#!/bin/bash
#numThread, host , port,  queryFile, logFile

if [[ $# -lt 1 ]] || [[ ! -f $1 ]] 
then
	echo "can't config"
	exit 1
fi

i=1
cat $1 |while read cmd
do
	[[ ${cmd} =~ '#' ]] && continue
	../bin/set_config.sh ${cmd} jmeter$i.jmx
	log_file=`echo ${cmd} | awk '{print $5}'`
	../bin/jmeter -nt jmeter$i.jmx -l ${log_file}
	i=$(($i+1))
done

exit 0


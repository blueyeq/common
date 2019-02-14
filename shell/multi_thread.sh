#!/bin/bash

files=(1 2 3 4 5 6 7 8 9 10 11 12 13)
echo 'len:' ${#files[@]}

len=${#files[@]}
thread=5
per_thread=$(( ${len}/${thread} ))
echo 'per_thread:' ${per_thread}
thread=$(( $((${len} + ${per_thread} - 1)) / ${per_thread} ))
echo 'thread:' ${thread}

echo ${per_thread}

for ((i=0;i<${thread}; ++i))
do
{
  for((j=0;j<${per_thread};++j))
  do
    index=$(($i*${per_thread} + $j))
    if [[ ${index} -ge ${len} ]]
      then
        break
      fi
      f=${files[${index}]}
      echo ${index}
  done
}&
done

exit 0


# sw=2;ts=2;sts=2;expandtab

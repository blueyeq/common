#!bin/bash
i=0
#rm -f ./combine
#rm -f ./com_tmp

if [ -e combine ]
	then
		rm -f  combine
	else
		echo 'not exist combine'
fi

if [ -e com_tmp ]
	then 
		rm -f com_tmp
	else 
		echo 'not exist com_tmp'
fi


for sub in $(ls ./) 
	do 
		if((i<12)) && [[ "$sub" =~ "^part-" ]]
			then
				echo ${sub}
				if [ -e combine ] 
					then 
						cat combine ${sub} >  com_tmp
						mv ./com_tmp ./combine
					else
						cp ${sub} combine
				fi
		fi	
		i=$[$i+1]
	done
echo $i

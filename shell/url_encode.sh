#!/bin/bash 

#make url code
od -t x  ~/test/query |awk '{ 
w=split($0,linedata," ");
for (j=2;j<w+1;j++)
{
	for (i=7;i>0;i=i-2)
	{
		if(substr(linedata[j], i, 2) == "0a"){
			printf "\n"
		}else if (substr(linedata[j],i,2) != "00") { 
			printf "%%"
			printf toupper(substr(linedata[j],i,2));
		}
	}
}
}' 

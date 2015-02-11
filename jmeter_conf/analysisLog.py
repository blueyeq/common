#/bin/python

import os
import sys
import time

def convTime(time_stamp):
	time_stamp = float(time_stamp)/1000 
	timeArray = time.localtime(float(time_stamp))
	date = time.strftime("%Y-%m-%d %H:%M:%S", timeArray)
	return date 

def analysis(log, time_interval):
	sum_line=0
	error_line=0
	success_req=0
	failed_req=0
	sum_latency=0

	max_latency=0
	min_latency=0

	start_time = -1;
	end_time = 0;

	fin = open(log)
	
	sub_suc=0
	sub_latency=0
	last_time=0

	for line in fin:
		#print line
		sum_line += 1
		line = line.strip()
		if line.find("OK") == -1:
		  failed_req += 1
		  continue

		item=line.split(",");
		if len(item) != 10:
		  error_line += 1
		  continue
		if start_time == -1:
		  start_time = item[0]
		  last_time = item[0]

		end_time = item[0]
		if max_latency < long(item[9]) :
		  max_latency = long(item[9])
		if min_latency == -1 or min_latency > long(item[9]):
		  min_latency = long(item[9])

		sum_latency += long(item[9])
		success_req += 1
		
		sub_suc += 1
		sub_latency += long(item[9])
		if long(item[0]) - long(last_time) > time_interval:
			print 'from:'+convTime(last_time)+"to:"+convTime
			print 'latency_time:', sub_latency / sub_suc

	fin.close()

	start_time = float(start_time)/1000
	end_time  = float(end_time)/1000 
	timeArray = time.localtime(float(start_time))
	start_date = time.strftime("%Y-%m-%d %H:%M:%S", timeArray)
	timeArray = time.localtime(float(end_time))
	end_date = time.strftime("%Y-%m-%d %H:%M:%S", timeArray)

	print 'start_date:', start_date
	print 'end_date: ', end_date
	print 'req_sum:',     sum_line
	print 'req_suc:', success_req
	print 'req_failed: ', failed_req
	print 'max_latency:', max_latency
	print 'min_latency:', min_latency
	if success_req > 0:	
	  print 'arvg_latency_time:', sum_latency / success_req

if __name__ == '__main__':
	if len(sys.argv) < 2:
		print 'wrong param'
		exit(1)
	else:
		analysis(sys.argv[1], len(sys.argv) == 3 and sys.argv[2] * 1000 or 60000)



#!/bin/env python
# -*- coding: utf-8 -*- 
# _*_ encoding: utf-8 _*_

import sys
import os
import codecs


def parseTag(line):
	left = 0
	res=''
	for ch in line:
		if   ch == '<':
			left = left + 1
		elif ch == '>':
			if left > 0:
				left = left - 1
		else:
			if left == 0:
				res += ch
		
	return res
def func(file_in, file_out):
	fin = codecs.open(file_in, 'r', 'utf-8')
	fout = codecs.open(file_out, 'w', 'utf-8')
	str = u'是同义词'	

	line_cnt=0
	error_line=0
	for line in fin:
		line = line.strip()
		line = line.replace(' ', '')
		line = line.replace('\t','')
		line = line.replace('</a>', '$')	
		line = parseTag(line)
		if line.find(u'是同义词') != -1:
			line=line[0:line.find(u'是同义词')]
		else:
			error_line = error_line + 1
		line = line.replace(u'$和','\t')
		line = line.replace('$', '')

		fout.write(line + '\n')
		line_cnt = line_cnt + 1
		if line_cnt % 1000 == 0:
			print line_cnt
	print 'error_line#', error_line
	print '  sum_line#', line_cnt
if __name__ == '__main__':
	func(sys.argv[1], sys.argv[2])





#!/bin/env python
# _*_ encoding: utf-8 _*_
# _*_ coding: utf-8 _*_

import sys
import os
import codecs


def filter(term_array):
	term_array.sort(key = lambda word:len(word))
	len_array = len(term_array)
	new_term_array = []
	for j in xrange(len_array):
		if len(term_array[j]) > 8:
			continue
		k = j + 1
		flag = 0
		while k < len_array and len(term_array[k]) <= 8:
			if term_array[k].find(term_array[j]) != -1:
				flag = 1
				break
			k = k + 1
		if flag == 0:
			new_term_array.append(term_array[j])
	return new_term_array

def function(file_in_name, file_out_name):
	fin = codecs.open(file_in_name, 'r', 'utf-8')
	fout = codecs.open(file_out_name, 'w', 'utf-8')
	
	for line in fin:
		line = line.strip()
		term_array = line.split('\t')
		if len(term_array) == 0:
			continue

		term_array = filter(term_array)
		if len(term_array) < 2:
			continue
		for j in xrange(len(term_array)):
			if j == 0:
				fout.write(term_array[0])
			else:
				fout.write('\t' + term_array[j])
		fout.write('\n')

if __name__ == '__main__':
	function(sys.argv[1], sys.argv[2])

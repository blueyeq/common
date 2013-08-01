#!/bin/env python
# _*_ encoding: utf-8


import sys
import os
import codecs

def init():
	global SUF_SET
	SUF_SET = {}
	

def calcSuffix(word):
	global	SUF_SET 
	word = word.strip()
	len_word = len(word)
	suf = ''
	while len_word > 0 :
		suf = word[len_word - 1] + suf
		if suf in SUF_SET:
			SUF_SET[suf] = SUF_SET[suf] + 1
		else:
			SUF_SET[suf] = 1
		len_word = len_word - 1

def sufWrite(suf_file):
	global	SUF_SET 
	file_suf = codecs.open(suf_file, "w", "utf-8")
	list_suf = sorted(SUF_SET.items(), key =lambda item:item[1], reverse=True)
	for key in list_suf:
		tkey = key[0].strip();
		file_suf.write('['+ tkey + ']\t' + str(key[1]) + '\n')

def function(file_in):
	fin = codecs.open(file_in, 'r', 'utf-8')
	for line in fin:

		term_array = line.split('\t')
		while term_array.count("") > 0:
			term_array.remove("")
		for term in term_array:
			if len(term) < 2:
				continue
			calcSuffix(term)
				


if __name__ == '__main__':

	init()
	function(sys.argv[1])
	sufWrite(sys.argv[2])


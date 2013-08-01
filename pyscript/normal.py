#!/bin/env python
# encoding: utf-8

import sys
import os
import codecs



def fileOpen(fin_name, fout_name):
	global fin
	global fout
	fin = codecs.open(fin_name, 'r', 'utf-8')
	fout = codecs.open(fout_name, 'w', 'utf-8')

def fileClose():
	global fin
	global fout
	fin.close()
	fout.close()
def init():
	global dict_replace
	global dict_strip
	dict_replace = {'(':'',')':'',']':'','[':'',u'（':'', u'）':'', u'【':'', u'】':'', u'《':'', u'》':'',u',':'', u'：':'\t', u'、':'\t', u'，':'\t', u'：':'\t', u'.':'', u':':'', u'·':'' ,u'!':'' , u'“':'', u'／':'', u'。':''}
	dict_strip   = ['&', '#', '$']

def isEnglishChar(ch):
	o = ord(ch) 
#print o
	if o<128 :
		return 1
	return 0
def isEnglishWord(word):
	for ch in word:
		if isEnglishChar(ch) == 0:
			return 0
	return 1

def change(word):
	global dict_replace
	
	for key in dict_replace:
	#	if word.find(key) != -1:
	#		print 'has:', key, word, '['+dict_replace[key]+']'
	#	else:
	#		print 'not has', key , word
		word = word.replace(key, dict_replace[key])
	return word

def ignoreLine(line):
	global dict_strip
	for key in dict_strip:
		if line.find(key) != -1:
			return 1

	return 0

def fileWrite(term_array, count):
	if count < 2:
		return
	global fout
	for i in xrange(count):
		fout.write(term_array[i] + '\t')
	fout.write('\n')


def function(file_in_name, file_out_name):
	fileOpen(file_in_name, file_out_name)
	global fin
	global fout
	file = []
	sum_line = 0
	error_line = 0
	for line in fin:
		sum_line = sum_line + 1
		line = line.strip()
		if ignoreLine(line) == 1:  # 跳过该行
			continue
		line = change(line)        # 修正特殊字符
		term_array = line.split('\t')
		count = 0
		word_array = []
		term_array.sort()
		for word in term_array:
			if isEnglishWord(word): #  跳过英文word
				continue
			tmp_word = word.strip()  # 调整term
			if (count == 0 or tmp_word != term_array[count - 1]) and len(tmp_word) > 1 : # 去重和保证word长度
				term_array[count] = tmp_word
				count = count + 1
				word_array.append(tmp_word)
	
		word_array.sort(lambda x,y: cmp(len(x), len(y)))   # 按word长度排序
		if len(word_array) > 1:
			file.append(word_array)
		else:
			error_line = error_line + 1
	

	file.sort(key=lambda words:len(words[0]))       # 按第一个word长度排序
	for line in file:
		for word in line:
			fout.write(word + '\t')
		fout.write('\n')

	fileClose()
	print 'error line#', error_line
	print 'sum   line#', sum_line

if __name__ == '__main__':

	init()
	function(sys.argv[1], sys.argv[2])


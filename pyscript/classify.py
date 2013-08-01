#!/bin/env python
# _*_ encoding: utf-8 _*_

import sys
import os
import codecs

fileEnglish = codecs.open("term-english", "w", 'utf-8')
fileSub     = codecs.open("term-sub", "w", 'utf-8')
fileOther   = codecs.open("term-other" , "w", 'utf-8')

def isStopChar(ch):
	if ch == ' ' or ch == ',' or ch == '.' or ch == '"' or ch == "'" or ch == '，' or ch == '。':
		return 1
	return 0

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

def fileOpen():
	print 'file open'


def fileClose():
	global fileEnglish
	global fileSub
	global fileOther

	fileEnglish.close()
	fileSub.close()
	fileOther.close()

def fileWriteEnglish(words, count):
	if count < 2 :
		return
	global fileEnglish
#print count
	for i in xrange(count):
		word = words[i]
		fileEnglish.write(word + '\t')
	fileEnglish.write('\n')

def fileWriteSub(words, count):
	if count < 2:
		return
	global fileSub
	for i in xrange(count):
		word = words[i]
		fileSub.write(word + '\t')
	fileSub.write('\n')

def isSubsequence(str1, str2):
	len_s1 = len(str1)
	len_s2 = len(str2)
	pre = -1
	for i in xrange(len_s1):
		exist_ch = 0
		for j in xrange(pre + 1, len_s2):
			if(str1[i] == str2[j]):
				exist_ch = 1
				pre = j;
				break;
		if exist_ch == 0:
			return 0

	return 1


def fileWriteOther(words, count):
	if count < 2:
		return
	global fileOther
	for i in xrange(count):
		word = words[i]
		fileOther.write(word + '\t')
	fileOther.write('\n')

def classify(agency_file):

	fin = codecs.open(agency_file, "r", 'utf-8')
	fileOpen()

	for line in fin:
#		print line
		term_array = line.split('\t')
		if len( term_array ) == 0:
			continue
		term_array.remove('')	
		term_array.sort()
		count = 0;
		len_term = len(term_array)
		isEnglish = 0
		for i in xrange( 0, len_term, 1 ):
			word = term_array[i]
			if word.find(':') != -1:                                  # [typ:word] 
				word = word[word.find(':')  + 1: word.find(']')]
			if count > 0 and  word == term_array[count - 1]:          # 和前一个词相同
				continue
			if word == u'查看编辑版本':                                # 错词
				continue
			if word.count(' ') != 0 or word.count('.') != 0 or word.count(',') != 0 or word.count(';') != 0 and  word.count(u'·') != 0 and word.count(u'；') != 0:                             # 含有特殊字符
				continue
			if word.find('[') != -1:                                 # [A$B$..] tag信息行
				continue

			if isEnglishWord(word) == 1:
				isEnglish = 1
				continue
			word = word.replace(' ', '')
			term_array[count] = word
			count = count + 1;
#print word
		if count < 2:
			continue
		isEnglish = 1                              # 强制写到english文件中

#print 'is 0'
#print 'isEnglis', isEnglish
		if isEnglish == 1:  # write english title word
			fileWriteEnglish(term_array, count)
			continue
		isSub = 0
		for i in xrange( count ):
			for j in xrange( count ):
				if j == i:
					continue
				if isSubsequence(term_array[i], term_array[j]) == 1:
					isSub = 1
			if isSub == 1:
				break
		if isSub :
			fileWriteSub(term_array, count)
		else:
			fileWriteOther(term_array, count)

	fileClose()

if __name__ == '__main__':
	classify(sys.argv[1])
#print isEnglishChar('a')	

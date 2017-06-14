#!/bin/env python
# _*_ encoding: utf-8 _*_
# _*_ coding: utf-8   _*_
# encoding: utf-8

import sys
import os
import codecs


def mySort(file_in_name, file_out_name):
  fin = codecs.open(file_in_name, 'r', 'utf-8')
  fout = codecs.open(file_out_name, 'w', 'utf-8')
  
  file = []
  for line in fin:
    line = line.strip()
    term_array = line.split('\t')
    while term_array.count('') > 0:
      term_array.remove('')
    if len(term_array) < 1:
      continue
    term_array.sort(key = lambda term:len(term))
    file.append(term_array)
  file.sort(key = lambda terms: len(terms[0]))
  
  for term_array in file:
    for j in xrange( len(term_array)):
      if j == 0:
        fout.write(term_array[0])
      else:
        fout.write('\t'+term_array[j])
    fout.write('\n')
  

if __name__ == '__main__':
  mySort( sys.argv[1], sys.argv[2])


# sw=2;ts=2;sts=2;expandtab

#! /usr/bin/env python
# -*- coding: utf-8 -*- 

import sys
import string
import os

kMaxNumber = 1000000

def get_father(x, father):
  if x < 0 or x >= kMaxNumber:
    return -1
  if x != father[x]:
    father[x] = get_father(father[x], father)
  return father[x]

if __name__ == "__main__":
  reload(sys)
  sys.setdefaultencoding("utf-8")

  ifilename = sys.argv[1]
  ofilename = sys.argv[2]
  father = range(kMaxNumber)
  dct = {}
  num = 0
  ifile = open(ifilename, "r")
  for line in ifile:
    line = line.decode("utf-8")
    line = line.strip()
    terms = line.split("\t")
    if len(terms) < 2:
      print line
      continue
    base_word_id = -1
    if terms[0] in dct:
      base_word_id = dct[terms[0]]
    else:
      base_word_id = num
      dct[terms[0]] = num
      num += 1
    if base_word_id == 44:
      print 'base word', terms[0], base_word_id
      print  line
    fbase = get_father(base_word_id, father)
    for term in terms[1:]:
      word_id = -1
      if term in dct:
        word_id = dct[term]
      else:
        word_id = num
        dct[term] = num
        num += 1
      fa = get_father(word_id, father)
      father[fa] = fbase
      if base_word_id == 44:
        print 'term index > 0', term, word_id
  ifile.close()
  print "# uniq terms: %d"%(num,)

  rdct = {}
  for key in dct:
    word_id = dct[key]
    gid = get_father(father[word_id], father)
    if gid not in rdct:
      rdct[gid] = set()
    rdct[gid].add(key)
  ofile = open(ofilename, "w")
  for key in rdct:
	ofile.write(str(key) + ";" +"%s\n"%("\t".join(rdct[key])))
  ofile.close()


#!/bin/python
import argparse


def parseArg():
  parser = argparse.ArgumentParser()
  parser.add_argument("-i","--int",type=int,help="int value")
  parser.add_argument("-s","--str",type=str,help="string value")
  args=parser.parse_args()
  print 'i=',args.int
  print 'str=',args.str
if __name__ == '__main__':
  parseArg()
# sw=2;ts=2;sts=2;expandtab

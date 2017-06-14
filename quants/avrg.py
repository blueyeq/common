#!/bin/env python

eles=[]
deltas=[0.5,0.61,-0.22,-0.35,0.79,0.04,0.15,0.70,-0.51,-0.41]


def avg():
  global eles
  sum=0.0
  for e in eles:
    print e
    sum += e
  v_avg = 0
  if len(eles) > 0:
    v_avg = sum / len(eles)
  print 'avg:',v_avg

def init():
  v=0
  global eles
  sum=0.0
  for vd in deltas:
    v += vd
    sum += vd*vd
    print v
    eles.append(v) 
  print 'sum:',sum

if __name__ == '__main__':
  init()
  avg()

# sw=2;ts=2;sts=2;expandtab

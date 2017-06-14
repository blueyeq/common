#!/bin/python

INPUT='/Users/linyu/Documents/sy/divide/vid-sec2.txt'
OUTPUT='/Users/linyu/Documents/sy/divide/vid-sec2.txt.out'

def uniq(file_in,file_out):
  fin=open(file_in,"r");
  fout=open(file_out,"w");
  lines=[]
  for line in fin:
    line = line.strip()
    lines.append(line)
  lines.sort()
  count=-1
  pre=''
  new_lines=[]
  for line in lines:
    if pre != line:
      if count > 0:
        new_lines.append((pre,count))
      pre = line
      count = 1
    else:
      count+=1
  if count > 0:
    new_lines.append((pre,count))
  new_lines.sort(key = lambda x:x[1],reverse=True)
  for line in new_lines:
    fout.write(line[0]+'\t'+str(line[1])+'\n')
  print 'processed:',len(lines)
  fin.close()
  fout.close()

if __name__ == '__main__':
  uniq(INPUT,OUTPUT)

# sw=2;ts=2;sts=2;expandtab

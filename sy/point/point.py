#!/bin/python
point_input="/Users/linyu/Documents/sy/point/point.txt"
point_out="/Users/linyu/Documents/sy/point/point_out.txt"


def process():
  file_in=open(point_input,"r")
  file_out=open(point_out,"w")
  sum_line=0
  error_line=0
  
  last_id = -1
  last_items =[-1.0,-1.0]

  for line in file_in:
    sum_line += 1
    if sum_line == 1:
      continue
    line = line.strip()
    items = line.split("\t")
    #for item in items:
      #print item
    now_id = items[0]
    if last_id == now_id:
      print last_items[1],last_items[2], items[1],items[2]
      file_out.write(str(last_items[1])+'\t'+str(last_items[2]) +'\t'
                      +str(items[1])+'\t'+str(items[2])+'\r\n' )
    last_id = now_id
    last_items = items

  print 'sum_line:',sum_line
  print 'error_line:',error_line;
  file_in.close()
  file_out.close()

if __name__ == '__main__':
  process();
# sw=2;ts=2;sts=2;expandtab

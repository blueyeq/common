#/bin/python

file1='mat1.txt'
file2='mat2.txt'

def compare(f1,f2):
  fin1=open(f1,'r')
  fin2=open(f2,'r')
  l1='' 
  line_count=0
  same_count=0
  diff_count=0
  for l1 in fin1:
    l2 = fin2.readline()
    l1=l1.strip()
    l2=l2.strip()
    #print l1,l2
    values1=l1.split()
    values2=l2.split()
    line_count += 1
    for i in xrange(0,len(values1),1):
      #print values1[i],values2[i]
      if values1[i] == values2[i]:
        same_count += 1
      else:
        diff_count += 1
  print 'lines:',line_count
  print 'same:',same_count
  print 'diff:',diff_count

if __name__ == '__main__':
    compare(file1,file2)

# sw=2;ts=2;sts=2;expandtab

import math

sq2=math.sqrt(2.0)
def f(n):
  if n == 0:
    return 0
  #nn=int(math.floor((sq2-1)*n))
  nn=long(math.floor((sq2-1)*n))
  if nn < 0:
    print '======error'
  return n*nn+n*(n+1)/2-nn*(nn+1)/2-f(nn)
def sqt(n):
  l=1
  r=n
  while l < r:
    mid=l+(r-l+1)/2
    v=mid*mid
    if v <= n:
      l=mid
    else:
      r=mid-1
  return l
def f2(n):
      global sq2
      if n <= 0:
          return 0
      nn=sqt(2*n*n)-n
      s=n*nn+n*(n+1)/2-nn*(nn+1)/2-f2(nn)
      return int(s)
def answer(str_n):
    num=int(str_n)
    if str(num) != str_n:
      print 'not eq'
    return f2(num)
def force(sn):
  n=int(sn)
  s=0
  for i in xrange(1,n+1):
    s += int(math.floor(math.sqrt(2)*i))
  return s
if __name__ == '__main__':
  print f(5)
  print f(77777779101112131415161718192021)
  print answer("1")
  print answer("2")
  print answer("3")
  print answer("4")
  print answer("77777779101112131415161718192021")
  for i in xrange(1,1000000):
      #print i,sqt(i),int(math.floor(math.sqrt(i)))
      if sqt(i) != int(math.floor(math.sqrt(i))):
        print 'sqt error',i,sqt(i),int(math.floor(math.sqrt(i)))
  print 'step 2'
  for i in xrange(0,5):
    j=10
    #if force(str(j+i)) != answer(str(j+i)):
    #  print 'error not eq:',i
    if f(j+i) != answer(str(j+i)):
      print 'error not eq:',i
    #print i,force(str(i))
    #print i,answer(str(i))
# sw=2;ts=2;sts=2;expandtab

import math
#g_dict={"a":1}
g_ans=0
g_line=[]
g_dict={}
inv={}

#equal
def cmp_interval(x,v1,v2):
  return x > min(v1,v2) and x < max(v1,v2)
def cmp_interval_eq(x,v1,v2):
  return x >= min(v1,v2) and x <= max(v1,v2)
#TODO not eq
def inner(a,b,line):
    #print 'try:',a,b,line
    if a[0] == b[0]:# vertical
        return cmp_interval(a[0],line[0],line[2]) and cmp_interval(line[1],a[1],b[1]) and line[0] != line[2]
    if a[1] == b[1]:# horizonral
        return cmp_interval(a[1],line[1],line[3]) and cmp_interval(line[0],a[0],b[0]) and line[1] != line[3]
    k=(1.0)*(b[1]-a[1])/(b[0]-a[0])
    if line[0] == line[2]:
        y=k*(line[0]-a[0])+a[1]
        #print y,a,b,line
        return cmp_interval(y,line[1],line[3]) and cmp_interval(y,a[1],b[1]) and cmp_interval(line[0],a[0],b[0])
    else:
        x=a[0]+1.0*(line[1]-a[1])/k
        #print x,a,b,line
        return cmp_interval(x,line[0],line[2]) and cmp_interval(x,a[0],b[0]) and cmp_interval(line[1],a[1],b[1])
def distance(s,e):
    x=1.0*(e[1]-s[1])*(e[1]-s[1])+(e[0]-s[0])*(e[0]-s[0])
    return math.sqrt(x)

def pir(p,line):
    res=[]
    if line[0] == line[2]:
        res.append(2*line[0]-p[0])
        res.append(p[1])
    else:
        res.append(p[0])
        res.append(2*line[1]-p[1])
    #print p,line,res
    return res
# x in the segment a-b
def getx(a,b,x):
    if (not cmp_interval_eq(x[0],a[0],b[0])) or (not cmp_interval_eq(x[1],a[1],b[1])):
        return False
    if a[0] == b[0]:
      return x[0] == a[0] and cmp_interval_eq(x[1],a[1],b[1])
    k=(1.0)*(b[1]-a[1])/(b[0]-a[0])
    y=k*(x[0]-a[0])+a[1]
    return y == x[1]

def valid(ps,s,e):
    l=len(ps)-1
    v=e
    #print ps,e
    while l >= 0:
      if not inner(ps[l],v,g_line[ps[l][2]]):
        return True 
      if getx(ps[l],v,s):
        #print 'f1:',ps[l],v,ps[0]
        return False
      if v!=e and getx(ps[l],v,e):
        #print 'f2:',ps[l],v,e
        return False
      v=pir(v,g_line[ps[l][2]])
      l -= 1
    if getx(s,v,e):
        return False
    dd=(ps[len(ps)-1][0],ps[len(ps)-1][1])
    global g_dict
    if g_dict.has_key(dd):
      return False
    print ps[len(ps)-1]
    print ps,s,e,v[0]-s[0],v[1]-s[1]
    #g_dict[(v[0]-s[0],v[1]-s[1])]=1
    g_dict[dd]=1
    return True 
def dfs(ps,pre,s,e,dis,dep,dd,status):
    #print ps, pre
    global g_ans
    global g_line
    p=ps[len(ps)-1]
    #if dep % 40 == 0:
    #  print dep,str(p)
    if distance(p,e) > dis:
        return
    if status == 15 and p[2] == ps[0][2] and p[3] == ps[0][3]:
        #print 'return'
        return
    if valid(ps,s,e):
        g_ans += 1
    for i in xrange(1,3):
        nline=(pre+i*dd+4)%4
        nd=(i==2 and -dd or dd)
        np=pir(p,g_line[nline])
        np.append(nline)
        np.append(nd)
        ps.append(np)
        dfs(ps,nline,s,e,dis,dep+1,nd,status|(1<<nline))
        ps.pop(len(ps)-1)
def answer2(d, p, e, dist):
    global g_ans
    global g_line
    global g_dict
    g_ans=0
    g_line=[]
    g_dict={}
    a=[0,0,0,d[1],0,1,0];   g_line.append(a) # y
    a=[0,d[1],d[0],d[1],d[1],0,1];  g_line.append(a) #xx
    a=[d[0],0,d[0],d[1],d[0],0,0];  g_line.append(a) #yy
    a=[0,0,d[0],0,0,1,1];  g_line.append(a) # x
    if distance(p,e) < dist:
        g_dict[(p[0],p[1])]=1
        g_ans += 1
    #print g_line
    for i in xrange(0,4):
      for j in [-1,1]:
          np=pir(p,g_line[i])
          np.append(i)
          np.append(j)
          ps=[]
          ps.append(np)
          dfs(ps,i,p,e,dist*1.0,0,j,1<<i)
    print g_dict
    return len(g_dict)

def check(p,s,e,mid):
  p=[p[0],p[1]]
  pre=-1
  ee=e
  global g_line
  global inv
  #print 'check:',p,s,e,mid
  step=0
  sc=[0,0,0,0]
  op=p
  w=mid[1][0]
  h=mid[2][1]
  lastp=[]
  while True:
    lastp.append((p[0],p[1],ee[0],ee[1]))
    for v in mid:
    #  print p,e,v
      if v!= p and v != ee and getx(p,ee,v):
        print 'getx:',p,ee, v
        return False
    if p == s:
      break
    found=False
    for i in xrange(0,4):
      if pre != i and inner(p,ee,g_line[i]):
        print 'found:',p,ee,g_line[i], 
        ee=pir(ee,g_line[i])
        p=pir(p,g_line[i])
        pre=i
        found=True
        sc[i] += 1
        #if (p[0],p[1],ee[0],ee[1]) in inv:
        #  print 'find in inv',p,e
        #  return False
        print '->',p,ee
        break
    if not found:
      #print 'not found:',p,ee,sc
      return False
    step += 1
  #print step,sc
  return True
def gao(x,y,e,dist):
  global g_ans
  global g_dict
  p=[x,y]
  if distance(p,e) <= dist:
    #g_dict[(p[0],p[1])] = 1
    g_ans += 1
    #print p
    return True
  return False

def answer3(d,p,e,dist):
  w=d[0]
  h=d[1]
  cnt=0
  xs=p[0]
  ys=p[1]
  k=0
  global g_dict
  t_dict=g_dict
  g_dict={}
  while True:
    pa=g_ans
    for i in [1,-1]:
      for j in [1,-1]:
        y=2*k*h*i*j+ys*i
        #print y, ys,e[1]
        if y == ys or  xs != e[0] or True:
          gao(xs,y,e,dist)
        if ys != e[1] or y != ys or True:
          #print y,-xs, ys,e[1]
          gao(-xs,y,e,dist) #1
          gao(2*w-xs,y,e,dist) #1
          gao(-2*w+xs,y,e,dist) #2
          gao(2*w+xs,y,e,dist) #2
          gao(4*w-xs,y,e,dist) #3
          gao(-2*w-xs,y,e,dist) #3
          gao(-4*w+xs,y,e,dist) #4
          gao(4*w+xs,y,e,dist) #4
    if pa==g_ans:
      break
    k += 1
  k=0
  #print '\nx:'
  while True:
    pa=g_ans
    for i in [-1,1]:
      for j in [1,-1]:
        x=2*k*w*i*j+xs*i
        #print k,w,i,j
        #print x,ys,-ys,2*h-ys
        if ys != e[1] or True:
          gao(x,ys,e,dist)
        if xs != e[0] or x != xs or True:
          gao(x,-ys,e,dist) #1
          gao(x,2*h-ys,e,dist) #1
          gao(x,2*h+ys,e,dist) #2
          gao(x,-2*h+ys,e,dist) #2
          gao(x,4*h-ys,e,dist) #3
          gao(x,-2*h-ys,e,dist) #3
          gao(x,-4*h+ys,e,dist) #4
          gao(x,4*h+ys,e,dist) #4
    if pa == g_ans:
      break
    k += 1
  #print 'len:',len(g_dict)
  global g_line
  g_line=[]
  a=[0,0,w,0];  g_line.append(a) # y
  a=[0,0,0,h];  g_line.append(a) #xx
  a=[0,h,w,h];  g_line.append(a) #yy
  a=[w,0,w,h];  g_line.append(a) # x

  cnt=0
  end_p=[[0,0],[w,0],[0,h],[w,h],[xs,ys],[e[0],e[1]]]
  tt_dict={}
  for v in g_dict:
    #print 'v:',v
    if v != p:
      if check(v,p,e,end_p):
          cnt += 1
          tt_dict[v]=1
#          print cnt
#      else:
#        print 'invalid:',v,p
#  print t_dict
#  print tt_dict
  return cnt

def answer4(d,p,e,dist):
  w=d[0]
  h=d[1]
  cnt=0
  xs=p[0]
  ys=p[1]
  k=0
  global g_dict
  t_dict=g_dict
  g_dict={}
  end_p=[[0,0],[w,0],[0,h],[w,h],[xs,ys],[e[0],e[1]]]
  global g_line
  g_line=[]
  a=[0,0,w,0];  g_line.append(a) # y
  a=[0,0,0,h];  g_line.append(a) #xx
  a=[0,h,w,h];  g_line.append(a) #yy
  a=[w,0,w,h];  g_line.append(a) # x
  while True:
    pa=g_ans
    for i in [1,-1]:
      for j in [1,-1]:
        y=2*k*h*i*j+ys*i
        kk=0
        pre=0
        while True:
          pb=g_ans
          for l in [1,-1]:
            for m in [1,-1]:
              x=2*kk*w*l*m+xs*l
              if gao(x,y,e,dist):
                v=[x,y]
                g_dict[(x,y)]=1
                if (k+kk<1000000) and (not check(v,p,e,end_p)): # {2h-y y-2h 4h-y y-4h} {-y 2h+y,-2h-y,4h+y}
                  #if kk % 2 == 0:
                  #print k*i*j,i,kk*l*m,l,kk*l*m-pre
                  pre=kk*l*m
          if pb == g_ans or (k < 0 and kk < 0):
            break
          kk += 1
    if pa==g_ans:
      break
    k += 1
  #print 'len:',len(g_dict)
  #print len(g_dict)
  global inv
  inv={}
  cnt=0
  end_p=[[0,0],[w,0],[0,h],[w,h],[xs,ys],[e[0],e[1]]]
  #end_p=[[0,0],[w,0],[0,h]]
  tt_dict={}
  idd=0
  pre=-1
  for v in g_dict:
    #print 'v:',v
    idd += 1
    if v != p:
      if check(v,p,e,end_p):
          cnt += 1
          tt_dict[v]=1
#          print cnt
      else:
        #print 'invalid:',idd-pre,v,p
        pre=idd
#  print t_dict
  #print tt_dict
  g_dict=tt_dict
  return cnt

def answer5(d,p,e,dist):
  w=d[0]
  h=d[1]
  xs=p[0]
  ys=p[1]
  k=0
  global g_dict
  #print 'g_dict',g_dict
  t_dict=g_dict
  g_dict={}
  end_p=[[0,0],[w,0],[0,h],[w,h]]
  global g_line
  g_line=[]
  a=[0,0,w,0];  g_line.append(a) # y
  a=[0,0,0,h];  g_line.append(a) #xx
  a=[0,h,w,h];  g_line.append(a) #yy
  a=[w,0,w,h];  g_line.append(a) # x
  invalid_s={}
  invalid_e={}
  ans=0
  cnt=0
  for v in end_p:
    for vv in [[e[0],e[1]],[xs,ys]]:
      x=v[0];y=v[1]
      dx=x-vv[0]
      dy=y-vv[1]
      #print 'scanf:',x,y
      t2=0
      while True:
        x += dx
        y += dy
        if vv[0] == xs and vv[1] == ys:
          invalid_s[(x,y)]=1
          print 'add s: ',x,y
        else:
          invalid_e[(x,y)]=1
          print 'add e: ',x,y
        if not gao(x,y,vv,dist):
          t2 += 1
          if t2 > 4:
            break
  t1=0
  while True:
    pa=ans
    for i in [1,-1]:
      for j in [1,-1]:
        y=2*k*h*i*j+ys*i
        kk=0
        pre=0
        t2=0
        while True:
          pb=ans
          for l in [1,-1]:
            for m in [1,-1]:
              x=2*kk*w*l*m+xs*l
              #print 'xy:',x,y,k,i*j,i,kk,l*m,l
              if gao(x,y,e,dist):
                ans += 1
                #print 'xy:',(x,y)
                if (not invalid_s.has_key((x,y))) and not( (p[0] == e[0] and x == p[0] and y != p[1]) or (p[1] == e[1] and y == p[1] and x != p[0]) ):
                  found=1
                  if e[0] != x:
                    flag=1
                    xx=0
                    yy=0
                    if (i*j<0 and i<0) or (i*j>0 and i<0):
                      flag=-flag
                    if (m*l<0 and l<0) or (m*l>0 and l<0):
                      flag=-flag
                    if i*j*i > 0:
                      yy=0
                    else:
                      yy=h
                    if m*l*l > 0:
                      xx=0
                    else:
                      xx=w
                    #print 'xx yy:',x,y,xx,yy,flag
                    if flag*(y-e[1])*(xs-xx) == (x-e[0])*(ys-yy):
                      found=0
                      print 'found=',flag,(x,y),v
                #  print ans,(x,y)
                  if found == 1 and (not ((x,y) in g_dict)):
                    g_dict[(x,y)] = 1
                    cnt += found 
                  dx=x-e[0]
                  dy=y-e[1]
                  for st in [1]:
                    nx=x;ny=y
                    if st==-1:
                      dx=e[0]-x;dy=e[1]-y
                      nx=e[0]+2*dx;ny=e[1]+2*dy
                    else:
                      dx=x-e[0];dy=y-e[1]
                      nx=x+dx;ny=y+dy
                    while True:
                      if invalid_s.has_key((nx,ny)):
                        break
                      invalid_s[(nx,ny)]=1
                      print 'nx,ny',(nx,ny),(x,y),st
                      if not gao(nx,ny,e,dist):
                        break
                      nx += dx
                      ny += dy
#                    print nx,ny,x,y,dx,dy
          if pb == ans:
#            print 'break============'
            t2 += 1
            if t2 > 4:
              break
          kk += 1
    if pa==ans:
      t1 += 1
      if t2 > 4:
        break
    k += 1
  for v in g_dict:
    if v in invalid_s:
      cnt -=1
      print 'cnt--'
    elif not v in t_dict:
      print 'not in',v
#      print 'cnt--'
  cnt_need=0
#  for v in t_dict:
#    if not (v in g_dict):
#      print 'need',cnt_need,v
#      cnt_need +=1
  #print g_dict
#  print invalid_p
  print len(t_dict),cnt_need
  print t_dict
  print g_dict
  return  cnt
def gcd(a,b):
  if b == 0:
    return a
  return gcd(b,a%b)

def answer(d,p,e,dist):
  w=d[0]
  h=d[1]
  global g_dict
  #print 'g_dict',g_dict
  t_dict=g_dict
  g_dict={}
  end_p=[[0,0],[w,0],[0,h],[w,h]]
  global g_line
  g_line=[]
  a=[0,0,w,0];  g_line.append(a) # y
  a=[0,0,0,h];  g_line.append(a) #xx
  a=[0,h,w,h];  g_line.append(a) #yy
  a=[w,0,w,h];  g_line.append(a) # x
  invalid_s={}
  invalid_e={}
  ans=0
  cnt=0
  for v in end_p:
    for vv in [e,p]:
      k=-1
      add_cnt=0
      while True:
        k += 1
        tmp1=add_cnt
        for i in [1,-1]:
          for j in [1,-1]:
            kk=-1
            while True:
              kk += 1
              tmp2=add_cnt
              for m in [1,-1]:
                for l in [1,-1]:
                  vx=2*k*w*i*j+v[0]*i; vy=2*kk*h*m*l+v[1]*l 
                  dx=vx-vv[0]; dy=vy-vv[1]
                  g=gcd(abs(dx),abs(dy))
                  dx /= g; dy /=g
                  while True:
                    if vv == e:
                      invalid_s[(vx,vy)] = 1
                    else:
                      invalid_e[(vx,vy)] = 1
                    vx += dx
                    vy += dy
                    if not gao(vx,vy,vv,dist):
                      break
                    add_cnt += 1
              if tmp2==add_cnt:
                break
        if tmp1 == add_cnt:
          break
  t1=0
  k=0
  while True:
    pa=ans
    for i in [1,-1]:
      for j in [1,-1]:
        ys=2*k*h*i*j+p[1]*i
        ye=2*k*h*i*j+e[1]*i
        kk=0
        pre=0
        t2=0
        while True:
          pb=ans
          for l in [1,-1]:
            for m in [1,-1]:
              xs=2*kk*w*l*m+p[0]*l
              xe=2*kk*w*l*m+e[0]*l
              #print 'xy:',x,y,k,i*j,i,kk,l*m,l
              if gao(xs,ys,e,dist) or gao(xe,ye,p,dist):
                ans += 1
                if (not invalid_s.has_key((xs,ys))) or (not invalid_e.has_key((xe,ye))):
                  if not((xs,ys) in g_dict) and gao(xs,ys,e,dist) and (not invalid_s.has_key((xs,ys))):
                    g_dict[(xs,ys)] = (2*kk*m*l,l,2*k*i*j,i)
          #          print 'put:',(xs,ys)
                  v_i=0
                  for v in [[xs,xs-e[0],ys,ys-e[1]],[xe,xe-p[0],ye,ye-p[1]]]:
                    v_i += 1
                    dx=v[1];dy=v[3]
                    g=gcd(abs(dx),abs(dy))
                    dx /= g; dy /=g
                    t3=0
                    nx=v[0]+dx;ny=v[2]+dy
                    while True:
                  #    if invalid_s.has_key((nx,ny)):
                  #      break
                      if v_i == 1:
                        rx=abs(abs(nx)%(2*w))
                        ry=abs(abs(ny)%(2*h))
                        if (rx == p[0] or rx == 2*w-p[0]) and (ry == p[1] or ry == 2*h -p[1]):
                          invalid_s[(nx,ny)]=1
                        else:
                          invalid_s[(nx,ny)]=2
                          #print (nx,ny),v,dx,dy,g,p
         #               print 's nx,ny',(nx,ny),v,dx,dy,g
                      else:
                        rx=abs(abs(nx)%(2*w))
                        ry=abs(abs(ny)%(2*h))
                        if (rx==e[0] or rx==2*w-e[0]) and (ry == e[1] or ry == 2*h-e[1]):
                          invalid_e[(nx,ny)]=1
         #               print 'e nx,ny',(nx,ny),v
                      if not gao(nx,ny,e,dist):
                        t3 += 1
                        if t3>4:
                          break
                      nx += dx
                      ny += dy
#                    print nx,ny,x,y,dx,dy
          if pb == ans:
#            print 'break============'
            t2 += 1
            if t2 > 4:
              break
          kk += 1
    if pa==ans:
      t1 += 1
      if t2 > 4:
        break
    k += 1
  ans=0
  ans_dict={}
  for v in g_dict:
    if e[0] == p[0] and v[0] == p[0] and (not (v[1] == p[1])):
        continue
    if e[1] == p[1] and v[1] == p[1] and (not (v[0] == p[0])):
        continue
    if not (v in invalid_s):
        value=g_dict[v]
        xe=(value[0])*w+value[1]*e[0]
        if value[1] > 0:
          xe=-value[0]*w+value[1]*e[0]
        ye=(value[2])*h+value[3]*e[1]
        if value[3] > 0:
          ye=-value[2]*h+value[3]*e[1]
        if not( (xe,ye) in invalid_e):
          ans += 1
          ans_dict[v]=1
        #else:
        #  print 'in e:',v,(xe,ye)
    else:
      if invalid_s[v] == 2:
        print 'vvv:',v
    #    print 'in s:',v
#      print 'cnt--'
#  cnt_need=0
#  for v in t_dict:
#    if not (v in g_dict):
#      print 'need',cnt_need,v
#      cnt_need +=1
#  for v in ans_dict:
#    if not (v in t_dict):
#      print 'not in',cnt_need,v
#      cnt_need +=1
  #print g_dict
#  print invalid_p
  #print t_dict
  #print ans_dict
#  print len(t_dict)
#  end_p=[[0,0],[w,0],[0,h],[w,h],p,[e[0],e[1]]]
  #print 'ssss'
#  check([91, 108],p,e,end_p)
  return ans
if __name__ == '__main__':
#  print answer([3, 2],[1, 1],[2, 1],4*1.0)
#  print answer4([3, 2],[1, 1],[2, 1],4*1.0)
#  print answer2([3, 2],[1, 1],[2, 1],4*1.0)
#  print answer([300, 275],[150, 150],[185, 100],500)
#  print answer2([5, 5],[2, 1],[2, 2],17)
  #print answer([5, 5],[1, 1],[2, 2],4)
  #print answer4([2, 5],[1, 2],[1, 4],300)
  print answer([2, 5],[1, 2],[1, 4],300)
  #print gcd(4,2),gcd(abs(-2),4),gcd(12,abs(-18)),gcd(18,12)

#  print answer4([2, 5],[1, 2],[1, 4],69)
#  print answer([2, 5],[1, 2],[1, 4],69)
  #print answer([2, 5],[1, 2],[1, 4],1001)
  #print answer([2, 5],[1, 2],[1, 4],1001)
  #print answer4([42, 59],[36, 44],[6, 34],500)
  #print answer([42, 59],[36, 44],[6, 34],500)
#  print answer4([42, 59],[36, 44],[6, 34],5000)
  print answer([42, 59],[36, 44],[6, 34],5000)
# sw=2;ts=2;sts=2;expandtab

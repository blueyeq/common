g_id=0
g_ans=[]
def dfs(k,m,x,n,eles):
    global g_id
    global g_ans
    if k == m:
        for e in eles:
            g_ans[e].append(g_id)
        g_id += 1
        return
    for i in xrange(x,n):
        eles.append(i)
        dfs(k+1,m,i+1,n,eles)
        eles.remove(i)
def answer(num_buns, num_required):
    global g_id
    global g_ans
    g_id=0
    g_ans=[]
    for i in xrange(0,num_buns):
        g_ans.append([])
    dfs(0,num_buns-num_required+1,0,num_buns,[])
    return g_ans
if __name__ == '__main__':
  print answer(5,3)
  print answer(3,3)
  print answer(3,1)
# sw=2;ts=2;sts=2;expandtab

from datetime import datetime

s='2018-04-01 23:15:59.824'
t=datetime.strptime(s,'%Y-%m-%d %H:%M:%S.%f')
print t
print (t.minute)/10 * 10
t2=t.replace(minute=t.minute/10*10)
#df.apply(lambda x: x['TS'].replace(minute=int(int(x['TS'].minute)/int(gap) * gap) ),axis=1)
print t2
# sw=2;ts=2;sts=2;expandtab

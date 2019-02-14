
RATE=0.046
MONTHY_COST=6500
MONTHS=360
TOTAL=1230000

def calculateMonth():
    sum = 0.0
    global RATE
    RATE = RATE / 12.0
    count=0
    for i in xrange(1,MONTHS+1,1):
        sum += MONTHY_COST * pow(1+RATE,(MONTHS - i))
        count += 1
    print count
    print sum
    total_rate = sum / TOTAL
    print 'total_rate',total_rate
    print 'yearly_rate',pow(total_rate,1.0/(MONTHS/12.0)) 
if __name__ == '__main__':
    calculateMonth()

# sw=2;ts=2;sts=2;expandtab

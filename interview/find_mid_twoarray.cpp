#include <stdio.h>
#include <algorithm>

using namespace std;

void find(int a[], int n1, int b[], int n2)
{
  int mid=(n1+n2+1)>>1;
  int la(0), lb(0);
  int res=-1;
  while(mid>0){
    int mmid=(mid+1)>>1;
    if(a[min(n1-1,la+mmid-1)] < b[min(n2-1,lb+mmid-1)]){
      la += mmid;
      res=max(res,a[la-1]); // not sure in a[] or in b[]
    }else{
      lb += mmid;
      res=max(res,b[lb-1]);
    }
    mid -= mmid;
  }
  printf("%d %d %d\n",la,lb,res);
}

int main()
{
  int a[] = {0,1,3,4,8,11};
  int b[] = {2,5,7,9,10,12};
  find(a,sizeof(a)/sizeof(int),b,sizeof(b)/sizeof(int));


  return 0;
}
/* sw=2;ts=2;sts=2;expandtab */

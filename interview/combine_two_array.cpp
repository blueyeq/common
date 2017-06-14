/*
 * given an integer stream, ouput all the mid integers
 */
#include <stdio.h>
#include <queue>
using namespace std;

// a a a a b b b b
// a a a a b b b b
void print(int a[] , int len)
{
  for(int i = 0; i < len;++i){
    printf("%d ",a[i]);
  }
  puts("");
}

void combine(int a[],int n, int b[], int m)
{
  for(int i = m+n-1;i >= m;--i) a[i] = a[i-m];
  int len(n+m);
  int i(0),ia(m),ib(0);
  while(len--){
    if(ia < m+n && ib < m){
      if(a[ia] < b[ib]) a[i++] = a[ia++];
      else a[i++] = b[ib++];
    }
    if(ia >= m+n) a[i++] = b[ib++];
    if(ib>=m) break;
  } 
  for(int i = 0; i<m+n; ++i) printf("%d ",a[i]);
  puts("");
}

int main()
{
  //4 5 6 7
  //0 1 2 3 4 5                 5             5           6        6
  int a[100] = {9,10,11,12,13};  // {1 2 4 6 3} {1 2 3 6 4} {1 2 3 4 6} {1 2 3 4 5 6}
  int b[] = {1,2,3,5};
  combine(a,5,b,sizeof(b)/sizeof(int));
  return 0;
}
/* sw=2;ts=2;sts=2;expandtab */

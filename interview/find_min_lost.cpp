/*
 * find the min lost number in the give int array
 * a[] = {1,2,5} => 0
 * a[] = {0,7,9,3,4,1,2} => 5
 */

#include <stdio.h>
#include <cstring>
#include <algorithm>

int findMin(int a[], int s, int n)
{
  if(n <= 1){
    //printf("%d %d %d",s,a[0],n);
    if(n<1) return s;
    return a[0] == s ? s+1:s;
  }
  int mid=a[n>>1];
  int l(0), r(n-1);
  while(l<r){
    while(l<r && a[l] <= mid) ++l;
    while(l<r && a[r] > mid) --r;
    if(l<r) std::swap(a[l],a[r]);
  }
  //{...mid...}  { ....}
  printf("1:%d %d %d %d %d\n",l,r,a[l],n,mid);
  while(a[l] > mid) --l;
  printf("2:%d %d %d %d\n",l,r,mid,s+l);
  if(a[l] != mid) std::swap(a[n>>1],a[l]);
  if(mid > s+l) {
    return findMin(a,s,l);
  }else{
    printf("3:%d %d %d %d\n",l,r,mid,a[l+1]);
   // printf("%d %d\n",a[0],a[1]);
    return findMin(a+l+1,mid+1,n-l-1);
  }
}

int find(int a[], int n)
{
  return findMin(a,1,n); 
}


int main()
{
//  int a[] = {0,1,5,2}; // ...
  int a[] = {2,2,2,2}; // ...
//  int a[] = {0,6,5,3,4,1,2};
  printf("%d\n",find(a,sizeof(a)/sizeof(int)));
  return 0;
}
/* sw=2;ts=2;sts=2;expandtab */

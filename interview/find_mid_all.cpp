/*
 * given an integer stream, ouput all the mid integers
 */
#include <stdio.h>
#include <queue>
using namespace std;

void findMid(int a[], int n)
{
  priority_queue<int,vector<int>, greater<int> > big;
  priority_queue<int,vector<int>, less<int> > small;
  for(int i = 0; i < n; ++i){
    if(small.size() > 0 && small.top() > a[i]){
      small.push(a[i]);
      if(big.size() + 1 < small.size()){
        big.push(small.top());
        small.pop();
      }
    }else{
      big.push(a[i]);
      if(big.size() > small.size()) {
        small.push(big.top());
        big.pop();
      }
    }
    printf("%d %d %d %d\n",small.top(),big.top(), small.size(),big.size());
  }
}

int main()
{
  //0 1 2 3 4 5 
  int a[] = {1,5,2,4,3,0,7};
  findMid(a,sizeof(a)/sizeof(int));
  return 0;
}
/* sw=2;ts=2;sts=2;expandtab */

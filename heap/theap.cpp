#include "heap.h"
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <vector>


struct CmpSample{
  bool operator () (const int* a, const int* b) const
  {
    if(*a==*b){
      printf("error %d\n",*a);
    }
    return *a > *b;
  }
};

int* heap_buf[100000];
util::AdjustHeap<int*,CmpSample> heap;
std::vector<int> g_times1;
std::vector<int> g_times2;

int64_t g_time_sum1;
int64_t g_time_sum2;

void heap_sort(int a[], int n, int k)
{
  clock_t t_s = clock();
  CmpSample cmp; 
  printf("k=%d\n",k);
  for(int i = 0; i < n; ++i){
    //printf("i=%d\n",i);
    if(i<k){
      heap_buf[i] = &a[i];
      std::push_heap(heap_buf,heap_buf+i,cmp);
    }else if(cmp(&a[i],heap_buf[0])){
      std::pop_heap(heap_buf,heap_buf+k,cmp);
      heap_buf[k-1] = &a[i];
      std::push_heap(heap_buf,heap_buf+k,cmp);
    }
  }
  for(int i = 0; i < k; ++i){
    int *j = heap_buf[0];
    std::pop_heap(heap_buf,heap_buf+k-i,cmp);
    //printf("%d ",*j);
  }
  clock_t t_e = clock();
  printf("time_1:%ld\n",t_e - t_s);
  g_times1.push_back(t_e-t_s);
}

void sort_heap_adjust(int a[], int n, int k)
{
  clock_t t_s = clock();
  heap.clear();
  heap.setTopK(k);
  for(int i = 0; i < n; ++i){
    heap.push(&a[i]);
    //heap.print();
  }
  while(!heap.empty()){
    int *v = heap.pop();
    //printf("%d ",*v);
  }
  clock_t t_e = clock();
  printf("time_2:%ld\n",t_e - t_s);
  g_times2.push_back(t_e-t_s);
}

int main()
{
  int n = 10000;
  int k = 10000;
  //int *a = (int*) malloc(sizeof(int) * n);
  int *a =  new int[n];
  for(int i = 0; i < n; ++i){
    a[i] = i;
  }
  srand(time(NULL));
  for(int i = 0; i < n; ++i){
    int j = random() % n;
    int k = random() % n;
    //printf("j=%d k=%d\n",j,k);
    std::swap(a[j],a[k]);
  }
  if (!heap.init(n)) {
    printf("heap init failed.\n");
  }
  g_times1.clear();
  g_times2.clear();
  for(int i = 0; i< 30;++i){
    sort_heap_adjust(a,n,k);
    heap_sort(a,n,k);
  }
  sort(g_times1.begin(),g_times1.end());
  sort(g_times2.begin(),g_times2.end());
  for(int i = 1; i < g_times1.size() - 1; ++i){
    printf("%d %d  %d\n",i,g_times1[i],g_times2[i]);
    g_time_sum1 += g_times1[i];
    g_time_sum2 += g_times2[i];
  }

  printf("%lld %lld  %lld %lld\n",g_time_sum1,g_time_sum2,g_time_sum1/(g_times1.size()-2),g_time_sum2/(g_times2.size()-2));
  
  printf("%d done.\n",CLOCKS_PER_SEC);
  return 0;
}
/* sw=2;ts=2;sts=2;expandtab */

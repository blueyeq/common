#include "stdAfx.h"
#include <stdio.h>
#include <vector>

using namespace std;

const int N = 165;
const int M = 2356;

int sec2car[N+1][M+1];
int sec2sec[N+1][N+1];

void readin()
{
  FILE *fin = freopen("vid_sec_mat.txt","r", stdin);
  memset(sec2car,-1,sizeof(sec2car));
  for(int i = 0; i < N; ++i){
    for(int j = 0; j < M; ++j){
      scanf("%d",&sec2car[i][j]);
    }
  }
  printf("%d %d\n",N,M);
  memset(sec2sec,-1,sizeof(sec2sec));
  for(int j = 0; j < M; ++j){
    vector<int> sections;
    for(int i = 0; i < N; ++i){
      sec2sec[i][i] = 0;
      //if(sec2car[i][j] == 2) break;
      if(sec2car[i][j] == 1) {
        for(int k = 0; k < sections.size(); ++k){
       //   printf("%d ",sections[k]);
          sec2sec[i][sections[k]] = 1;
          sec2sec[sections[k]][i] = 1;
        }
        sections.push_back(i);
      }
    }
  }
  printf("%d %d\n",N,M);
  fclose(fin);
}

void calc_dis()
{
  bool update=true;
  while(update){
    update = false;
    for(int i = 0; i < N; ++i){
      for(int j = 0; j < N; ++j){
        for(int k = 0; k < N; ++k){
          if(sec2sec[i][k] != -1 && sec2sec[k][j] != -1){
            if(sec2sec[i][j] == -1 || sec2sec[i][j] > sec2sec[i][k] + sec2sec[k][j]){
              sec2sec[i][j] = sec2sec[i][k] + sec2sec[k][j];
              update = true;
            }
          }
        }
      }
    }
  }

  FILE* fout = freopen("sec_dis.txt","w",stdout);
  for(int i = 0; i < N; ++i){
    for(int j = 0; j < N; ++j){
      if(j == N-1) printf("%d\n",sec2sec[i][j]);
      else printf("%d ",sec2sec[i][j]);
    }
  }
  fclose(fout);
}

int main()
{
  readin();
  calc_dis();
  return 0;
}

/* sw=2;ts=2;sts=2;expandtab */

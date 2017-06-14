#include <stdio.h>
#include <cstring>
#include <string>

using namespace std;
const int N=4*1024*1024;
char buf[N];

void encode(string &name)
{

  string outname=name+".encode";
  FILE *in = fopen(name.c_str(),"r+");
  FILE *out = fopen(outname.c_str(),"w+");
  if(in == NULL || out == NULL){
    printf("open file[%s] failed.",name.c_str());
    return;
  }
  fwrite(buf,sizeof(char),N,out);
  int n;
  while((n=fread(buf,sizeof(char),N,in))>0){
    fwrite(buf,sizeof(char),n,out);
  }
  printf("n=%d\n",n);
  fclose(in);
  fclose(out);
}

void decode(string &name)
{
  string outname=name+".decode";
  FILE *in = fopen(name.c_str(),"r+");
  FILE *out = fopen(outname.c_str(),"w+");
  if(in == NULL || out == NULL){
    printf("open file[%s] failed.",name.c_str());
    return ;
  }
  int n;
  int cnt(0);
  while((n=fread(buf,sizeof(char),N,in))>0){
    if(cnt++>0){
      fwrite(buf,sizeof(char),n,out);
    }
  }
  fclose(in);
  fclose(out);
}

int main(int argc, char *argv[])
{
  if(argc < 2) {
    printf("wrong param :file,[e|d]\n");
    return 1;
  }
  printf("file:%s\n",argv[1]);
  string name(argv[1]);
  if(argv[2][0] == 'e') {
    encode(name);
  }else{
    decode(name);
  }
  return 0;
}
/* sw=2;ts=2;sts=2;expandtab */

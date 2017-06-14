#include <stdio.h>
#include <string>

// #a#b#c#c#b#e#b#c#c#b#a#s#d;
// 13131393131x131393
char src[1000];
int  p[1000];
int manacher(const char *s, const int src_len,const char *&palindrome)
{
  for(int i = 0; i < src_len; ++i){
    src[2*i] = '#';
    src[2*i+1] = s[i];
  }
  src[2*src_len] = 0;
  int len = 2*src_len;
  int mx(0), p_mx(-1);
  int ans_len(0);
  printf("s:%s\n",src);
  for(int i = 0;i < len; ++i){
    p[i] = mx > i ? p[2*p_mx-i] : 1;
    while(i+p[i] < len && i-p[i] >= 0
        && src[i+p[i]] == src[i-p[i]]){
      ++p[i];
    }
    if(i+p[i] > mx){
      mx = p[i] + i;
      p_mx = i;
    }
    if(p[i] > ans_len){
      ans_len = p[i];
      if(i&1){
        palindrome = s+(i/2)-p[i]/2+1;
      }else{
        palindrome = s+(i/2)-p[i]/2;
      }
    }
    printf("%d %c %d\n",i,src[i],p[i]);
  }
  return ans_len-1;
}

int main()
{
  //char str[] = "aradkad";
  char str[] = "abccbebccbasd";
  const char *palindrome=NULL;
  int len=manacher(str,strlen(str),palindrome);
  std::string s(palindrome,len);
  printf("%s\n",s.c_str());
  return 0;
}

/* sw=2;ts=2;sts=2;expandtab */

#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int g_block_size = 1;
int g_block_count = 1;

bool ParseArg(int argc, char* argv[])
{
  char c;
  int a;
  while ((c = getopt(argc, argv,"b:c:h")) != -1) {
    switch(c){
      case 'b':
        a = atoi(optarg);
        if (a > 0) {
          g_block_size = a;
        }
        break;
      case 'c':
        a = atoi(optarg);
        if (a > 0) {
          g_block_count = a;
        }
        break;
      default:
        printf("-b block_size[MB] -c block_count\n");
        return false;
    }
  }
  return true;
}

int main(int argc, char* argv[])
{
  if (!ParseArg(argc, argv)) {
    return false;
  }
  int block_count(0);
  struct timeval time_start, time_now;
  gettimeofday(&time_start,NULL);
  printf("[%ld %d]begin clear ...\n",time_start.tv_sec,time_start.tv_usec/1000);
  while( block_count < g_block_count) {
    ++block_count;
    void* p = malloc(1024 * 1024 * g_block_size);
    memset(p,0,1024 * 1024 * g_block_size);
    gettimeofday(&time_now,NULL);
    printf("[%ld %d] count[%d] sum size[%dMB]\n",time_now.tv_sec,time_now.tv_usec/1000,
          block_count, block_count * g_block_size);
  }
  printf("clear done.\n");
}
/* sw=2;ts=2;sts=2;expandtab */

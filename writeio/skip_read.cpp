#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <string>

char *file_in;
char *file_out;
int skip_count;

bool parseArg(int argc, char **argv)
{
  char c;
  while ((c = getopt(argc, argv, "s:i:o:h")) != -1) {
    switch (c) {
    case 'i':
			file_in = optarg;
      break;
    case 'o':
			file_out = optarg;
      break;
		case 's':
			skip_count = atoi(optarg);
    case 'h':
    default:
      fprintf(stderr, "usage:\t -s block_size -c block_count -p port\n");
      return false;
    }
  }
  return true;
}

const int BUF_SIZE = 1024*1024;
char buf[BUF_SIZE + 1];

void skip_read(char *fi, char *fo, int skip_bytes) {
	FILE* fip = fopen(fi,"rb+");
	FILE* fop = fopen(fo,"wb+");
  fseek(fip,0,SEEK_SET + skip_bytes);
	size_t n = 1;
  while(n > 0){
    n = fread((void*)buf,BUF_SIZE,1,fip);
    n = fwrite((void*)buf,BUF_SIZE,1,fop);
  }
	fclose(fip);
	fclose(fop);
}
int main(int argc, char **argv)
{
  if(!parseArg(argc,argv)){
    fprintf(stdout,"parseArg failed.\n");
    return 1;
  }
	printf("%s %s %d",file_in, file_out, skip_count)
	skip_read(file_in, file_out, skip_count);
  char buf[100];
  scanf("%s",buf);
  return 0;
}
/* sw=2;ts=2;sts=2;expandtab */

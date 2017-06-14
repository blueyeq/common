#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <string>

int g_block_size;
int g_block_count;

std::string gen_file_name()
{
  FILE* fp = fopen("./file.count","rb+");
  int file_count=0;
  if(fp){
    fseek(fp,0,SEEK_SET);
    size_t n_r = fread((void*)&file_count,sizeof(file_count),1,fp);
    fprintf(stdout,"nr[%zu] file_count[%d]  %m\n",n_r,file_count);
  }
  file_count++;
  if(fp){
    fseek(fp,0,SEEK_SET);
    size_t n_w = fwrite(&file_count,sizeof(int),1,fp);
    fprintf(stdout,"file_count[%d],nw[%zu]\n",file_count,n_w);
    fclose(fp);
  }else{
    fprintf(stdout,"write failed.");
  }
  char buf[256]; 
  snprintf(buf,256,"myfile.bin.%d",file_count); 
  std::string file_name(buf);
  fprintf(stdout,"file_name[%s]\n",file_name.c_str());
  return file_name;
}

void write_data()
{
  std::vector<char*> buffers;
  clock_t tbufs=clock();
  for(int i = 0; i < g_block_count; ++i){
    char * buf = (char*) malloc(g_block_size * 1024);
    if(!buf){
      fprintf(stdout,"malloc buf failed.\n");
      return;
    }
    for(int j = 0; j < g_block_size * 1024; ++j){
      buf[i] = (j+i) & 125;
    }
    if((i & 125) == 0){
      fprintf(stdout,"malloc block_count[%d]...\n",i);
    }
    buffers.push_back(buf);
  }
  clock_t tbufe=clock();
  fprintf(stdout,"malloc block done. cost[%ld]\n input any char continue write data..\n",(tbufe-tbufs)/1000);
  char buf[100];
  scanf("%s",buf);
  std::string name=gen_file_name();
  FILE* fp = fopen(name.c_str(),"wb");  
  setvbuf(fp,NULL,_IONBF,0);
  if(!fp){
    fprintf(stdout,"open myfile.bin mode[wb] failed.\n");
    return;
  }
  for(int i = 0; i < g_block_count; ++i){
    fwrite(buffers[i],g_block_size * 1024, 1,fp);
    if((i & 125) == 0){
      fprintf(stdout,"write block_count[%d]...\n",i);
    }
  }
  clock_t twe=clock();
  fprintf(stdout,"malloc block done. cost[%ld]\n input any char continue write data..\n",(twe-tbufe)/1000);
  for(int i = 0; i < g_block_count; ++i){
    free(buffers[i]);
  }
  fclose(fp);
  fprintf(stdout,"done.\n");
}

bool parseArg(int argc, char **argv)
{
  g_block_count = 1024;
  g_block_size = 1024;
  char c;
  while ((c = getopt(argc, argv, "s:c:h")) != -1) {
    switch (c) {
    case 's':
      g_block_size = atoi(optarg);
      break;
    case 'c':
      g_block_count = atoi(optarg);
      break;
    case 'h':
    default:
      fprintf(stderr, "usage:\t -s block_size -c block_count -p port\n");
      return false;
    }
  }
  fprintf(stdout,"block_size[%d]K block_count[%d]\n",g_block_size,g_block_count);
  return true;
}

int main(int argc, char **argv)
{
  if(!parseArg(argc,argv)){
    fprintf(stdout,"parseArg failed.\n");
    return 1;
  }
  write_data(); 
  char buf[100];
  scanf("%s",buf);
  return 0;
}
/* sw=2;ts=2;sts=2;expandtab */

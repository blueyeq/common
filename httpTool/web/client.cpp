
#include <iostream>

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <errno.h> 
#include <unistd.h> 
#include <netinet/in.h> 
#include <limits.h> 
#include <netdb.h> 
#include <arpa/inet.h> 
#include <ctype.h> 

#define MAXBUFRECV  2048
#define MAXBUFSEND  2048 
#define http_log(f) printf("%s %d %s\n", __FILE__, __LINE__, f)

using namespace std;

int BUFSIZE=10000;
int PORT = 80;
struct chttpget{

	chttpget(){

	}
	std::string run(std::string url);
};


std::string chttpget::run(std::string url)
{

    
    string page;
    int sockfd, ret, i, h;
    struct sockaddr_in servaddr;
    char str[4096],buf[BUFSIZE];
    socklen_t len;
    fd_set t_set1;
    fd_set mask;
    struct timeval  tv;
 
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) 
    {
       printf("创建网络连接失败,本线程即将终止---socket error!\n");
       exit(0);
    };
 
 
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    //将域名转为ip地址
    struct hostent *host = gethostbyname("www.baidu.com");
    
    char* ipstr = (char *)inet_ntoa(*(struct in_addr *)(host->h_addr));
    if (inet_pton(AF_INET, ipstr, &servaddr.sin_addr) <= 0 )
    {
          printf("创建网络连接失败,本线程即将终止--inet_pton error!\n");
          exit(0);
    };
    // 非阻塞connect
     //int flags=fcntl(sockfd,F_GETFL,0);
     //fcntl(sockfd,F_SETFL,flags|O_NONBLOCK);
     ret =  connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));   
     if (-1 == ret)
     {
       printf("与远端建立了连接\n");
      if(errno != EINPROGRESS)
     {
       perror("connect");
       close(sockfd);
     }
 
     FD_ZERO(&mask);
     FD_SET(sockfd,&mask);
     tv.tv_sec = 1;
     tv.tv_usec = 0;
    
     switch(select(sockfd+1,NULL,&mask,NULL,&tv))
     {
     
      case -1:
      close(sockfd);
      case 0:
      close(sockfd);
     
      default:
      int error=0;
      socklen_t len = sizeof(int);
      if(getsockopt(sockfd,SOL_SOCKET,SO_ERROR,&error,&len))
      {
         if(0 == error)
        {
        printf("has connect");
        }
      }
     }
     }else if(0==ret)
     {
      printf("has connect\n");
     }


    memset(str, 0, 4096);
     // http协议请求字符串，每一行的后面一定要加\n隔开    
      strcat(str,"GET s?wd=sd&rsv_bp=0&ch=&tn=baidu&bar=&rsv_spt=3&ie=utf-8&rsv_sug3=1&rsv_sug=0&rsv_sug1=1&rsv_sug4=33&inputT=99222 HTTP/1.1\n");
      strcat(str, "Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, application/vnd.ms-excel, application/vnd.ms-powerpoint, application/msword, application/x-ms-application, application/x-ms-xbap, application/vnd.ms-xpsdocument, application/xaml+xml, */* \n");
      strcat(str, "Accept-Language: zh-cn\n");
      strcat(str,"User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; (R1 1.6); .NET CLR 2.0.50727; .NET CLR 3.0.04506.648; .NET CLR 3.5.21022; .NET CLR 3.0.4506.2152; .NET CLR 3.5.30729)\n");
     strcat(str,"Host:www.baidu.com\n");
      strcat(str,"Connection: Keep-Alive");
      strcat(str, "\r\n\r\n");
	  printf("send\n%s\n", str);
 ret = write(sockfd,str,strlen(str));
 
  if (ret < 0) 
  {
         printf("发送失败！错误代码是%d，错误信息是'%s'\n",errno, strerror(errno));
         exit(0);
  }
  else
  {
     printf("消息发送成功，共发送了%d个字节！\n\n", ret);
  }


      FD_ZERO(&t_set1);
      FD_SET(sockfd, &t_set1);


      while(1)
      {
   //设置超时为1秒，如果1秒还没有反应直接返回
             tv.tv_sec= 1;
              tv.tv_usec= 0;
              h= 0;
              memset(buf, 0, sizeof(buf));
              h= select(sockfd +1, &t_set1, NULL, NULL, &tv);
              if (h == 0)
              {
              close(sockfd);
                  return page;
              }
              if (h < 0) {
                      close(sockfd);
                      printf("在读取数据报文时SELECT检测到异常，该异常导致线程终止！\n");
                      return "";
              };
               if (h > 0){
                      memset(buf, 0, sizeof(buf));
                      
                      i= read(sockfd, buf, sizeof(buf));
                      
                      if(i>0)
                      {
                      page = page + buf;
                      
                      }else
                      {
                      close(sockfd);
                      return page;
                      }
   
              }
      }
      close(sockfd);
      return page;
}

int main(){

	struct chttpget hget;
	cout<<	hget.run("http://www.baidu.com/s?wd=sd&rsv_bp=0&ch=&tn=baidu&bar=&rsv_spt=3&ie=utf-8&rsv_sug3=1&rsv_sug=0&rsv_sug1=1&rsv_sug4=33&inputT=99222");
	
	return 0;
}


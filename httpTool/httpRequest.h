
#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

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


struct httpRequest{
	
	int sock_fd;	
	struct sockaddr_in server_addr;
	struct hosttent *host;
	struct hostent *phost;
	int portNum;
	char recv_buff[MAXBUFRECV];
	char send_buff[MAXBUFSEND];
	

	httpRequest(){
		sock_fd = -1;
		portNum = -1;

		memset((struct sockaddr_in *)&server_addr, 0, sizeof(struct sockaddr));
		
	}
	bool init(const char *ip, const char *port);
	bool setServerAddr(const char *ip);
	bool setServerPort(const char *port);
	bool setFamily(int family);
	int  makeRequest(char *send_str);
	int  getSock();
	bool getConnect();
	int  sendMsg(char *msg);
	int recvMsg();

		

};

#endif

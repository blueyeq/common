#include <stdio.h>
#include <httpRequest.h>


bool httpRequest::setServerAddr(const char *ip){
	int len_ip = strlen(ip);
	if(len_ip < 7)  {
		http_log("can not prase the given ip");
		return false;
	}
	for(int i = 0; i < len_ip; ++i){
		if(ip[i] == '.'){
			if(i == 0 || i == len_ip - 1 || ip[i - 1] == '.'){
				http_log("can not prase the given ip");
				return false;
			}
		}else if(ip[i] < '0' || ip[i] > '9'){
			http_log("can not prase the given ip");
			return false;
		}
	}
	server_addr.sin_addr.s_addr = inet_addr(ip);
	return true;
}

bool httpRequest::setServerPort(const char *port){
	int len_port = strlen(port);
	if(len_port > 8) {
		http_log("can not prase the given port");
		return false;// 不允许前导0
	}
	int portNum = 0;
	for(int i = 0; i < len_port; ++i){
		if(port[i] < '0' || port[i] > '9')  {

			http_log("can not prase the given port");
			return false;
		}
		portNum = portNum * 10 + port[i] - '0';
	}
	server_addr.sin_port = htons(portNum);
	return true;
}

bool httpRequest::setFamily(int family){
	server_addr.sin_family = family;
	return true;
}

int httpRequest::makeRequest(char *msg){
	//sprintf(send_buff,   "POST HTTP/1.1\r\nUser-Agent: Mozilla/5.0\r\nAccept: text/html\r\nAccept-Language: zh-CN,zh\r\nmsearch.htm?param=sep_fuzzy:1|sep_synm:1&count=10&code=1&kw=qihu&start=0\r\n");
	
	//char parameters[200] = "10.119.253.1:8360/msearch.htm?param=sep_fuzzy:1|sep_synm:1&count=10&code=1&kw=qihu&start=0";
	phost = gethostbyname("www.baidu.com");
	//printf("%s\n", inet_hostn(phost->h_addr));
	char parameters[200] = " index.html ";
	http_log("make msg");
	strcat(send_buff, "  GET /");
	strcat(send_buff, parameters);
	strcat(send_buff, "HTTP/1.1\r\n");
	strcat(send_buff, "Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash\r\n");
	strcat(send_buff, "Accept-Language: zh-cn\r\n");
	strcat(send_buff, "User-Agent: Mozilla/4.0\r\n");
	strcat(send_buff, "response-type: 1\r\n");
	strcat(send_buff, "Content-Type: application/x-www-form-urlencoded\r\n");
	strcat(send_buff, "host: 10.119.253.1\r\n");
	strcat(send_buff, "Content-length: 0\r\n");
	strcat(send_buff, "Connection: Keep-Alive\r\n");
	strcat(send_buff, "\r\n\r\n");
	
	//内容信息
	//strcat(send_buff, "10.119.253.1:9316/msearch.htm?param=sep_fuzzy:1|sep_synm:1&count=10&code=1&kw=qihu&start=0");
	//http_log(send_buff);
	printf("%s\n", send_buff);
	return strlen(send_buff);
	
}
int  httpRequest::getSock(){
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_fd < 0) http_log("get socket fail");
	return sock_fd;
}

bool httpRequest::getConnect(){
	int res = connect(sock_fd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr));
	if(res == -1){
		http_log("connect error");
	}
	return res != -1;
}

int httpRequest::sendMsg(char *msg){
	int len_req = makeRequest(msg);
	int total_send(0);
	while(total_send < len_req){
		total_send += write(sock_fd, send_buff + total_send, len_req - total_send );
	}
	http_log("send succ!") ;
	return total_send;
}

int httpRequest::recvMsg(){
	
	int total_recv(0), len;
	while( ( len = read(sock_fd, recv_buff, MAXBUFRECV - 1) ) > 0){
		printf("%s\n", recv_buff);
	}
	return total_recv;
}

bool httpRequest::init(const char *ip, const char *port){
	return setServerAddr(ip) && setServerPort(port) && setFamily(AF_INET)
		&& getSock() > -1 && getConnect();
}



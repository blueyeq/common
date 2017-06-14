#include <stdio.h>
#include <httpRequest.h>

int main(){

	struct httpRequest http_hander;
	puts("main");
	if(http_hander.init("15.15.5.143", "8080")){
		puts("init");
    char req_str[] = "/solr/item/select?q=*%3A*&wt=json&indent=true";
    //char req_str[] = "/search.php?q=content:abc";
		if(http_hander.sendMsg(req_str) > 0){
			puts("wait msg");
			http_hander.recvMsg();
			puts("recv msg");
		}else{
			http_log(" sendMsg faild");
		}
	}else {
		http_log(" init_faild");
	}	

	return 0;
}
/* sw=2;ts=2;sts=2;expandtab */

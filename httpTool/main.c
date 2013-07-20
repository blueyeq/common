#include <stdio.h>
#include <httpRequest.h>

int main(){

	struct httpRequest http_hander;
	puts("main");
	if(http_hander.init("10.119.110.21", "8080")){
		puts("init");
		if(http_hander.sendMsg("msearch.htm?param=sep_fuzzy:1|sep_synm:1&count=10&code=1&kw=qihu&start=0") > 0){
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

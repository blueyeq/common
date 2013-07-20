#include <stdio.h>
#include <cstring>

using namespace std;

int main(){
	
	for(int i = 0; i < 3; ++i){
		fork();
		printf("%d\n", i);
		flush();
	}


	return 0;
}

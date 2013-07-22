#include <stdio.h>
#include <cstring>
#include <string>
#include <algorithm>

#define MAXLEN 100000

int next[MAXLEN];
int match_all_pos[MAXLEN];

typedef struct{
	int match_all_cnt;	
	void get_next(char *buf, int len, int next[]){ // make the next arrary[] 
		int i(0), j(-1);
		next[0] = -1;
		for(; i < len; ){
			if(j == -1 || buf[i] == buf[j]){
				next[++i] = ++j;
			}else j = next[j];
		}
	}

	int process_kmp(char *bufm, int lenm, char *bufp, int lenp, int match_all_pos[]){
		if(lenm >= MAXLEN || lenp >= MAXLEN){
			fprintf(stderr, "length exceed limit\n");
			return 0;
		}
		if(lenm < lenp){
			return 0;
		}
		if(lenp == 0) {
			return lenm;
		}

		get_next(bufp, lenp, next);
		int i(0), j(0);
		match_all_cnt = 0;
		for(; i < lenm; ){
			if(j == -1 || bufm[i] == bufp[j]){
				++i; ++j;
				if(j == lenp)   match_all_pos[match_all_cnt++] = i - lenp;
			}else  j = next[j];
		}
		return match_all_cnt;
	}

}KMP;


#ifdef __TEST_KMP

void test(){
	char bufm[] = "use c++ to program is better than use c";
	char bufp[] = "usei c";
	KMP test_kmp;
	printf("%d\n", test_kmp.process_kmp(bufm, strlen(bufm), bufp, strlen(bufp), match_all_pos));
}

int main(){


	test();	

	return 0;
}

#endif


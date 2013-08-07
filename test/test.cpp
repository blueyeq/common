#include <stdio.h>
#include <cstring>
#include <string>

using namespace std;

int main(){

	uint8_t a[10];
	uint8_t *p1 = &a[0];
	uint8_t *p2 = &a[9];
	printf("%d\n", p2 - p1);
	return 0;
}

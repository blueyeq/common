#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

int main(){

	
	char line[1000];
	while(gets(line)){
		istringstream in(line);
		int num(0);
		string word;
		while(in>>word){
			if(++num > 2)  cout<<word<< " ";
		}
		cout<<endl;
	}
		


	return 0;
}

#include <stdio.h>
#include <cstring>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class delDig{

private:
	char input[20], output[20];
	fstream fin, fout;

public:
	
	delDig(char in[], char out[]){
		strcpy(input, in);
		strcpy(output, out);
	}

	bool open(){
		fin.open(input, ios::in);
		fout.open(output, ios::out);
		if(!fin || !fout){
			return false;
		}
		return true;
	}
	
	bool close(){
		fin.close();
		fout.close();
		return true;
	}
	
	void work(){
		open();
		char readbuf[2049];
		int cnt(0), maxLine(100000);

		while(!fin.getline(readbuf, 2048).fail()){

			string line(readbuf);
			bool flag(false);
			for(int i = 0; i < line.length(); ++i){
				if(line[i] >= '0' && line[i] <= '9'){
					flag = true;
				}
			}
			if(!flag && ++cnt < maxLine){
				fout<<line<<endl;
			}
		}

		close();

	}
};

void test(){

	delDig dd("sinput.tt", "tt.del");
	dd.work();
}

int main(){

	test();


	return 0;
}

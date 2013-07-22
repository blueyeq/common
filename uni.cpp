#include <stdio.h>
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>

//using namespace std;

class Uni{

private:
	char input[200];
	char output[200]; 
	
	std::ifstream fin;
	std::ofstream fout;

public:

	Uni(char in[], char out[]){
		
		strcpy(input, in);
		strcpy(output, out);
	
	}

	bool open(){

		fin.open(input, std::ios::in);
		fout.open(output, std::ios::out);
		if(!fin || !fout){
			std::cout<<"文件打开失败!"<<std::endl;
			return false;
		}
		
		return true;
	}
	
	bool close(){
		fin.close();
		fout.close();
		return true;
	}

	void uniq(char type){
		
		char lineBuff[5049];
		std::string pre, now;

		if(!open())  return;
		bool flag(false);

		while(!fin.getline(lineBuff, 5048).fail()){

			int len = strlen(lineBuff);
			now = std::string(lineBuff);
			
			if(type == 'd'){   //print the only  duplicate line  and one time 
				if(now == pre){
					flag = true;
				}else{
					if(flag)  fout<<pre<<std::endl;
					flag = false;
				}
			
			}
			if(type == 'u'){ //print the duplicate line one time

				if(now != pre){
					fout<<now<<std::endl;
				}
			}
			else if(type == 'i'){ // delete the duplicate line
				if(now == pre)   flag = true;
				else {
					if(!flag){
						if(pre.length() > 0) fout<<pre<<std::endl;
					}
					flag = false;
				}
			}
			pre = now;
		}

		if(pre.length() > 0){
			if(type == 'd' && flag){
				fout<<pre<<std::endl;
			}
			if(type =='i'){
				if(!flag) fout<<pre<<std::endl;
			}
		}
			

		close();
	}

};


int main(int argc, char *argv[]){
    
	printf("uni log start:\n");
	if(argc != 4)  {
		std::cout<<"wrong parameter"<<std::endl;
		printf("uni log end!\n");
		return -1;
	}
	Uni uniq(argv[2], argv[3]);
	uniq.uniq(argv[1][0]);

	printf("uni log end!\n");

	return 0;
}

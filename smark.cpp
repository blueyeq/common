#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;


int ingor(){

	ifstream fin("signed", ios::in);

	int lines;
	fin>>lines;
	fin.close();

	return lines;
}

void reset(int lines){

	ofstream fo("signed");
	fo<<lines<<endl;
	fo.close();
}

bool check(char ch[]){
	return strlen(ch) == 1 && ch[0] >= '0' && ch[0] <= '5';
}

int main(){
	
	int ing = ingor();
	cout<<ing<<endl;

	ifstream fin("sinput",ios::in);
	ofstream fout("soutput",ios::app);
	char linebuff[2048];
	
	int lineCnt(0);

	while(!fin.getline(linebuff,2048).fail()){
		
		if(++lineCnt <= ing)  continue;
		
		int spos = strchr(linebuff,'\t')-linebuff;
		string t1(linebuff,0,spos); 
		string t2(linebuff+spos+1); 
		cout << "候选对" << lineCnt << "：\t"<< t1 << "\t" << t2 << "\t";
		
		char typ[100] = {0};
		
		while(!check(typ)){
			if(typ[0] != 0)  cout<<"请输入正确格式："<<endl;
			cin>>typ;
			
		}

		if(typ[0]== '0')   break;

		switch(typ[0]){
			case '1':
				cout << "type 1: 任何时候可互相替换的同义词" << endl;
				break;
			case '2':
				cout << "type 2: 取决于上下文的同义词" << endl;
				break;
			case '3':
				cout << "type 3: 意义相关，但不是同义词" << endl;
				break;
			case '4':
				cout << "type 4: 同音词/错别字，但不是同义词" << endl;
				break;
			case '5':
				cout << "type 5: 毫不相关！" << endl;
				break;
		}
		fout << t1 << "\t" << t2 << "\t" << typ[0] << endl;
		if(lineCnt % 10 == 0)   {
			fout.flush();
			reset(lineCnt-1);
		}
	}
	fin.close();
	fout.close();
	reset(lineCnt - 1);
	return 0;
}

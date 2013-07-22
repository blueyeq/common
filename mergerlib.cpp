#include <stdio.h>
#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

#define MAXN 100000
#define pb push_back

map<string, int> dict;
vector<string> lib_word[MAXN];  
int otyp[MAXN], btyp[MAXN];   // the tpy of one line
int belong[MAXN * 10];   // word belong which row
int father[MAXN];

class Mergerlib{

private:
	int line_lib, word_id;
public:
	Mergerlib(){
		dict.clear();
		line_lib = word_id = 0;
	}
	
	~Mergerlib(){
		dict.clear();
		for(int i = 0; i < line_lib; ++i){
			lib_word[i].clear();
		}
	}
	//hash 
	int getId(string word){
		if(dict.find(word) == dict.end())  {
			belong[word_id] = -1;
			dict[word] = word_id++;
			
		}
		return dict[word];
	}
	// disjoin set	
	int find_father(int x){
		if(father[x] == x)  return x;
		return father[x] = find_father(father[x]);
	}
	// pass the point	
	string get_useful(char buf[], int len){
		string res="";
		int npoint(0);
		for(int i = 0; i < len; ++i){
			if(buf[i] == ',') {
				res += ' ';
				if(++npoint == 3)  return res;
			}else res += buf[i];
		}
		return "";
	}
	
	int isDigit(string word){
		int res(0);
		for(int i = 0; i < word.length(); ++i){
			char ch = word[i];
			if(ch >= '0' && ch <='9')   res = res * 10 + ch - '0';
			else  return -1;
		}
		return res;
	}


	string toLowletter(string str){
		for(int i = 0; i < str.length(); ++i){
			if(str[i] >= 'A' && str[i] <= 'Z'){
                 str[i] += 32;
             }   
         }   
         return str;
	}


	//  read conflict words to lib_word[]
	bool read_conflict(char in_conflict[]){

		char buf[5049];
		fstream fin(in_conflict, ios::in);
		if(!fin)  return false;

		line_lib = word_id = 0;
		dict.clear();
		string word;
		int num_print(0);

		while(!fin.getline(buf, 5048).fail()){
			string line = get_useful(buf, strlen(buf));
			//printf("conflict read:%d %s\n", otyp[line_lib], line.c_str());
			if(line.length() < 1)  continue;
			istringstream in(line);
			in>>otyp[line_lib];
			if(otyp[line_lib] == 2)  continue;  //  skip dump 
			//printf("conflict read:%d %s\n", (int)otyp[line_lib], buf);
			
			father[line_lib] = line_lib;	
			lib_word[line_lib].clear();
			while(in>>word){
				if(isDigit(word) > 0)  break;
				word = toLowletter(word);
				int id = getId(word);
				lib_word[line_lib].pb(word);
				if(belong[id] == -1)   belong[id] = line_lib;
				else  {
					int fa = find_father(belong[id]);
					if(btyp[fa] == btyp[line_lib]){
						father[ find_father(belong[id]) ] = line_lib;	
					}
				}
			}
			//printf("%d  %d\n", line_lib, lib_word[line_lib].size());
			btyp[line_lib++] = isDigit(word) > 0 ? isDigit(word) : 1;	
		}
		fin.close();
		/*
		for(int i = 0; i < line_lib; ++i){
			if(father[i] != i)   printf("%d  %d\n", i, father[i]);
		}
		*/
		printf("conflict read %d lines", line_lib);
		return true;
	}
    //  read lib_word to lib_word[]
	bool read_lib(char in_lib[]){

		fstream fin(in_lib, ios::in);
		if(!fin)  return false;

		char buf[2049];
		string word;
		int tmp_line_lib = line_lib;
		while(!fin.getline(buf, 2048).fail()){
			//printf("lib read: %s\n", buf);	
			father[line_lib] = line_lib;
			istringstream in(buf);
			in >> otyp[ line_lib ] >> btyp[ line_lib ];
			while(in>>word){
				word = toLowletter(word);
				int id = getId(word);
				lib_word[line_lib].pb(word);
				if(belong[id] == -1)  belong[id] = line_lib;
				else {
					int fa = find_father(belong[id]);
					if(btyp[fa] == btyp[line_lib]){
						father[ find_father(belong[id]) ] = line_lib;	
						/*	
						for(int k = 0; k < lib_word[fa].size(); ++k){
							printf("%s  ", lib_word[fa][k].c_str());
						}
						printf("<%s> %d  %d\n", word.c_str(), fa, line_lib);
						*/
					}
				}
			}
			++line_lib;
		}
		fin.close();
		printf("lib read %d lines\n", line_lib - tmp_line_lib);
		return true;
	}
	
	bool merger(char merger_out[]){
		
		fstream fout(merger_out, ios::out);
		if(!fout)  return false;
		
		int append_line(0);
		for(int i = 0; i < line_lib; ++i){
			int rowid = find_father(i);
			//printf("%d  %d\n", i, lib_word[i].size());
			if(rowid == i)  continue;
			append_line++;
			//printf("%d %d\n", rowid, i);	
			for(int j = 0; j < lib_word[i].size(); ++j){
				lib_word[rowid].pb(lib_word[i][j]);
			}
		}
		printf("append lines %d\n", append_line);
		int writeline(0);

		for(int i = 0; i < line_lib; ++i){
			int rowid = find_father(i);
			if(rowid != i)  continue;
			writeline++;
			sort(lib_word[i].begin(), lib_word[i].end());
			vector<string>::iterator it = unique(lib_word[i].begin(), lib_word[i].end());
			if(lib_word[i].size() < 2)  {
				/*printf("error %d\n", i);
				for(int j = 0; j < lib_word[i].size(); ++j){
					printf("%s  ", lib_word[i][j].c_str());
				}
				*/printf("\n");
				continue;
			}
			lib_word[i].erase(it, lib_word[i].end());
			fout<<otyp[i]<<"\t"<<btyp[i]<<"\t";
			for(int j = 0; j < lib_word[i].size(); ++j){
				fout<<lib_word[i][j]<<"\t";
			}
			fout<<endl;
		}
		printf("write line: %d %d\n", line_lib, writeline);
		fout.close();
		return true;
	}

};

int main(int argc, char *argv[]){
	
	printf("merger log start:\n");
	if(argc != 4){

		printf("wrong parameter!\n lib conflict newlib"); 
		printf("merger log end!\n");
		return -1;
	}else{
/*
		strcpy(argv[1], "i1");
		strcpy(argv[2], "i2");
		strcpy(argv[3], "i3");
*/
		Mergerlib mymerger;
		if(mymerger.read_conflict(argv[2])){
			if(mymerger.read_lib(argv[1])){
				if(mymerger.merger(argv[3])){
					printf("run success!\n");
				}
			}
		}

	}
	printf("merger log end!\n");



	return 0;
}

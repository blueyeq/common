#include <stdio.h>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>



using namespace std;

#define pb push_back

const int MAXN = 1000000;

map<string, int> dict;
vector<string> rowLib[MAXN];
int belong[MAXN * 2];
char  btyp[MAXN], otyp[MAXN];
char use[MAXN], vis[MAXN];
int contain[MAXN];

class Picklib{
	
private:
	char srclib[200], input[200], output[200], outputLeft[200];
	int cntWord;
	int lineLib;
public:

	Picklib(char src[], char in[], char out[], char left[] = "left"){
		strcpy(srclib, src);
		strcpy(input, in);
		strcpy(output, out);
		strcpy(outputLeft, left);
		//cout<<src<<" "<<in<<" "<<out<<" "<<left<<endl;
	}
		
	~Picklib(){
		dict.clear();
		for(int i = 0; i <=lineLib; ++i){
			rowLib[i].clear();
		}
		dict.clear();
	}
	
	int getId(string word){
		if(dict.find(word) == dict.end())  {
			dict[word] = cntWord;
			belong[cntWord++] = 0;
		}
		return dict[word];
	}
	

	string toLowletter(string str){
		for(int i = 0; i < str.length(); ++i){
			if(str[i] >= 'A' && str[i] <= 'Z'){
                 str[i] += 32;
             }   
         }   
         return str;
	}   
	
	bool readLib(){
		fstream fin(srclib, ios::in);
		char readbuf[5049];
		lineLib = cntWord = 0;
		dict.clear();
		while(!fin.getline(readbuf, 5048).fail()){
			use[ ++lineLib ] = 0;
			istringstream in(readbuf);
			//cout<<lineLib<<" "<<readbuf<<endl;
			int t1, t2;  in>>t1>>t2;
			otyp[lineLib] = t1;  
			btyp[lineLib] = t2;
			string word;
			rowLib[ lineLib ].clear();
			while(in>>word){
				word = toLowletter(word);
				int id = getId(word);
				
				rowLib[lineLib].pb(word);
				belong[id] = lineLib;
			}
					
		}
		cout<<"lineLib"<<lineLib<<endl;
		fin.close();
		return true;
	}
	
	bool pick(){
		fstream fin(input, ios::in);
		fstream foutIntse(output, ios::out);
		if(!fin || !foutIntse)  return false;
		memset(vis, 0, sizeof(vis));
		char readbuf[5049];
		while(!fin.getline(readbuf, 5048).fail()){
			istringstream in(readbuf);
			string word;
			vector<string> trow;  
			int cross(0);
			while(in>>word){
				word = toLowletter(word);
				int id = getId(word);
				if(belong[id] > 0)   contain[cross++] = belong[id];
				trow.pb(word);
				//foutIntse<<word<<" ";
				
			}
			sort(contain, contain + cross);
			cross = unique(contain, contain + cross) - contain;
			if(cross > 0){
				bool ild(true); // some line include it all
				for(int i = 0; i < cross; ++i){
					int rowid = contain[i];
					ild = true;
					for(int j = 0; j < trow.size(); ++j){
						string str1 = toLowletter(trow[j]);
						bool fg(false);
						for(int u = 0; u < rowLib[rowid].size(); ++u){
							string str2 = toLowletter(rowLib[rowid][u]);
							if(str1 == str2)  {
								fg = true;
								break;
							}
						}
						if(!fg)  ild = false;
					}
					if(ild)  break;
				}
				if(ild)   continue;
				bool conflict(false);
				for(int i = 0; i < cross; ++i){
					int rowid = contain[i];
					if(vis[rowid])   {
						conflict = true;
						break;   // if the row have append other line  don't append it	
					}
					vis[rowid] = 1;
					for(int j = 0; j < rowLib[rowid].size(); ++j){
						trow.pb(rowLib[rowid][j]);
					}
				}
				if(conflict)   {
					trow.clear();
					break;
				}

				sort(trow.begin(), trow.end());
				vector<string>::iterator del = unique(trow.begin(), trow.end());
				trow.erase(del, trow.end());

				for(int i = 0; i < trow.size(); ++i){
					foutIntse<<trow[i]<<" ";
				}
				foutIntse<<", ,";
				for(int i = 0; i < cross; ++i){
					int rowid = contain[i];
					use[rowid] = true;
					foutIntse<<"[ ";
					for(int j = 0; j < rowLib[rowid].size(); ++j){
						foutIntse<<rowLib[rowid][j]<<" ";
					}
					foutIntse<<"] "<<(int)btyp[rowid]<<" ";
				}
				trow.clear();	
				foutIntse<<endl;
			}
			
		}
		fin.close();
		//foutIntse.close();

		
		//fstream fin(input, ios::in);
		//fstream foutIntse(output, ios::out);
		fin.open(input, ios::in);
		//foutIntse.open(output, ios::app);
		int mycnt(0);	
		while(!fin.getline(readbuf, 5048).fail()){
			istringstream in(readbuf);
			string word;
			vector<string> trow;  
			int cross(0);
			while(in>>word){
				int id = getId(word);
				if(belong[id] > 0)   contain[cross++] = belong[id];
				trow.pb(word);
				//foutIntse<<word<<" ";
				
			}
			++mycnt;
			sort(contain, contain + cross);
			cross = unique(contain, contain + cross) - contain;
			if(cross == 0){
				for(int i = 0; i < trow.size(); ++i){
					foutIntse<<trow[i]<<" ";
				}
				foutIntse<<endl;
			}
			trow.clear();
		}
		fin.close();
		foutIntse.close();
		return true;

	}
	
	bool writeLeft(){
		fstream foutLeft(outputLeft, ios::out);
		for(int i = 1; i <= lineLib; ++i){
			if(use[i] || rowLib[i].size() == 0)  continue;
			foutLeft<<(int) otyp[i]<<" "<<(int) btyp[i];
			for(int j = 0; j < rowLib[i].size(); ++j){
				foutLeft<<" "<<rowLib[i][j];
			}
			foutLeft<<endl;
		}
		foutLeft.close();
		return true;
	}
};


int main(int argc, char *argv[]){

	printf("picklib log start:\n");
	
	if(argc < 4 || argc > 5){
		cout<<"wrong parameter!"<<endl;
		printf("picklib log end!\n");
		return -1;
	}
	else {
		if(argc == 4)  {
			Picklib work(argv[1], argv[2], argv[3]);
			if(work.readLib()){
				if(work.pick()){
					work.writeLeft();
				}
			}
		}
		if(argc == 5) {
			Picklib work(argv[1], argv[2], argv[3], argv[4]);
			if(work.readLib()){
				if(work.pick()){
					work.writeLeft();
				}
			}
		}
	}

	printf("picklib log end!\n");
	return 0;
}

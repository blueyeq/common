#include <stdio.h>
#include <cstring>
#include <string>
#include <algorithm>
#include <fstream>
#include <map>
#include <iostream>
#include <sstream>
#include <vector>


using namespace std;

//max term maxn * 2   if more  will get overflow
const int MAXN = 1000000;

			
map<string, int>  dict;
vector<string> row[MAXN * 2];   // result for everyline
int fa[MAXN * 2];   
bool vis[MAXN * 2];
class CombRow{

private:
	char input[200], output[200];  // filename for input & output
	fstream fin, fout;
	int cnt;    //  count for dict
public:
	CombRow(char in[], char out[]){
		strcpy(input, in);
		strcpy(output, out);
	}
	
	void open(){
		fin.open(input, ios::in);
		fout.open(output, ios::out);
	}

	void close(){
		fin.close();
		fout.close();
	}
	int getId(string word){    //  hash term table  by map
		
		if(cnt >= MAXN)  return 0;
		if(dict.find(word) == dict.end())   	{
			fa[cnt] = cnt;
			dict[word]=cnt++;
		}
		return dict[word];

	}

	string toLowletter(string word){
		for(int i = 0; i < word.length(); ++i){
			if(word[i] >= 'A' && word[i] <= 'Z')  word[i] += 32;
		}
		return word;
	
	}

	int find(int x){  // dij  set
		if(fa[x] == x)  return x;
		return fa[x] = find(fa[x]);
	}
	void seria(){   //give every term a id

		open();
		dict.clear();

		char readbuf[5049];
		string w1, w2;
		cnt = 0;
		while(!fin.getline(readbuf, 5048).fail()){
			//cout<<readbuf<<endl;	
			istringstream in(readbuf);
			if(in>>w1){
				if(in>>w2){
			//		cout<<w1<<"\t"<<w2<<endl;
					w1 = toLowletter(w1);
					w2 = toLowletter(w2);

					int id1 = getId(w1);
					int id2 = getId(w2);
					fa[find(id1)] = find(id2);
					while(in>>w1){
						int id1 = getId(w1);
						fa[find(id1)] = find(id2);
					}
				}else  cout<<"error word2"<<endl;
			}else cout<<"error word1"<<endl;
			
		}
		for(int i = 0; i < cnt; ++i){
			row[i].clear();
		}
		close();
	}
	void comb(){ // combine the row by hash table  and output it
	
		open();
	//	cout<<"cnt:"<<cnt<<endl;
		
		char readbuf[2049];
		string w1, w2;
		memset(vis, 0, sizeof(vis));
		int line1(0), line2(0);
		while(!fin.getline(readbuf, 2048).fail()){
		//	cout<<readbuf<<endl;
			istringstream in(readbuf);
			if(in>>w1){
				if(in>>w2){
					w1 = toLowletter(w1);
					w2 = toLowletter(w2);
					int nr = find(getId(w1));
					if(!vis[getId(w1)])	row[nr].push_back(w1);
					if(!vis[getId(w2)])  row[nr].push_back(w2);
					vis[getId(w1)] = vis[getId(w2)] = 1;
					
					while(in>>w1){
						w1 = toLowletter(w1);
						if(!vis[getId(w1)])   row[nr].push_back(w1);
						vis[getId(w1)] = 1;
					}
					
					++line1;
					
				}else cout<<"error w2"<<endl;

			}else  cout<<"error w1"<<endl;
		}
		for(int i = 0; i < cnt; ++i){
			
			sort(row[i].begin(), row[i].end());
			vector<string>::iterator del = unique(row[i].begin(), row[i].end());
			row[i].erase(del, row[i].end());
			if(row[i].size() > 1){
				
				++line2;
				fout<<row[i][0];
				string pre = row[i][0];	
				for(int j = 1; j < row[i].size(); ++j){
					if(row[i][j] != pre)  fout<<"\t"<<row[i][j];
					pre = row[i][j];
				}
				fout<<endl;
			}
		}

		close();
		dict.clear();
		cout<<line1<<"\t"<<line2<<endl;
	}

};

int main(int argc, char *argv[]){
	
	printf("combine row log start:\n");
	if(argc != 3)  {
		cout<<"wrong parameter";
		printf("combine row log end!\n");
		return -1;
	}else{
		CombRow comb(argv[1], argv[2]);
		cout<<argv[1]<<"\t"<<argv[2]<<endl;
		comb.seria();
		comb.comb();
	}
	printf("combine row log end!\n");

	return 0;
}

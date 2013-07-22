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

#define pb push_back

//max term maxn * 2   if more  will get overflow
const int MAXN = 1000000;

			
map<string, int>  dict;
vector<string> row[MAXN * 2], old[MAXN * 2];   // result for everyline

int fa[MAXN * 2], orgf[MAXN * 2], contain[MAXN];
char vis[MAXN * 2], use[MAXN * 2], ptyp[MAXN], typ[MAXN];
class CombRow{

private:
	char input[20], output[20];  // filename for input & output
	fstream fin, fout;
	int cnt, oldlineCnt;    //  count for dict
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
		
		if(cnt >= MAXN)  return -1;
		if(dict.find(word) == dict.end())   	{
			dict[word]=cnt++;
		}
		return dict[word];

	}
	void init(char in[]){
		fstream finit(in, ios::in);
		dict.clear();
		char readbuf[2049];
		cnt = 0;
		string w1, w2;
		memset(vis, 0, sizeof(vis));
		memset(use, 0, sizeof(use));
		int line(0);
		while(!finit.getline(readbuf, 2048).fail()){
			istringstream in(readbuf);
			cout<<line<<"\t"<<readbuf<<endl;	
			int t1, t2;
			if(in>>t1){
				if(in>>t2){
					typ[line] = t2;
				}else cout<<"error typ input"<<endl;
			}else cout<<"error process typ"<<endl;
			old[line].clear();
			if(in>>w1){
				if(in>>w2){
					int id1 = getId(w1);
					int id2 = getId(w2);
					//fa[find(id1)] = find(id2);
					fa[id1] = fa[id2] = line;
					vis[id1] = vis[id2] = 1;
					old[line].clear();
					old[line].pb(w1);
					old[line].pb(w2);
					while(in>>w1){
						id1 = getId(w1);
						old[line].pb(w1);
						fa[id1] = line;
						vis[id1] = 1;				 
					}
				
				}else cout<<"init w2 wrong"<<endl;
			}else cout<<"init w1 wrong"<<endl;
			++line;
		}
		oldlineCnt = line;
		finit.close();

	}

	void comb(){ // combine the row by hash table  and output it
	
		open();
	//	cout<<"cnt:"<<cnt<<endl;
		
		char readbuf[2049];
		string w1, w2;
		//memset(vis, 0, sizeof(vis));
		int line1(0), line2(0);
		while(!fin.getline(readbuf, 2048).fail()){
			cout<<readbuf<<endl;
			istringstream in(readbuf);
			if(in>>w1){
				if(in>>w2){
					vector<string> tmpline; 
					tmpline.clear();
					tmpline.pb(w1);
					tmpline.pb(w2);
					int id1 = getId(w1);
					int id2 = getId(w2);
					int corssline(0);
					if(vis[id1] == 1) contain[corssline++] = fa[id1];
					if(vis[id2] == 1) contain[corssline++] = fa[id2];
					while(in>>w1){
						id1 = getId(w1);
						if(vis[id1] == 1) contain[corssline++] = fa[id1];
						tmpline.pb(w1);
					}
					sort(contain, contain + corssline);
					corssline = unique(contain, contain + corssline) - contain;
					sort(tmpline.begin(), tmpline.end());
					//vector<string> ::iterator it = unique(tmpline.begin(), tmpline.end()) - tmpline.begin();
					//cout<<corssline<<endl;
					for(int i = 0; i < tmpline.size(); ++i){
						fout<<tmpline[i]<<"  ";
					//	cout<<i<<" :"<<tmpline[i]<<"  "<<endl;
					}
					
					if(corssline > 0){
						fout<<", , ";
						for(int i = 0; i < corssline; ++i){
							int rowid = contain[i];
							use[rowid] = true;
							fout<<"[  ";
							for(int j = 0; j < old[rowid].size(); ++j){
								fout<<old[rowid][j]<<"  ";
							}
							fout<<"  ]  "<<(int)typ[rowid]<<"  ";
						}
					}
					
					fout<<endl;
					
				}else cout<<"error w2"<<endl;

			}else  cout<<"error w1"<<endl;
		}
		cout<<"oldlineCnt "<<oldlineCnt<<endl;
		close();
		dict.clear();
		fstream ffout("left", ios::out);
		for(int i = 0; i < oldlineCnt; ++i){
			if(use[i])  continue;
			cout<<"not use "<<i<<endl;
			ffout<<ptyp[i]<<"\t"<<typ[i]<<"\t";
			for(int j = 0; j < old[i].size(); ++j){
				ffout<<old[i][j]<<"\t";
			}
			ffout<<endl;
		}
		ffout.close();
		cout<<line1<<"\t"<<line2<<endl;
	}

};

int main(int argc, char *argv[]){
	
	if(argc != 4)  {
		cout<<"wrong parameter";
	}else{
		
		CombRow comb(argv[2], argv[3]);
		comb.init(argv[1]);
		cout<<argv[1]<<"\t"<<argv[2]<<"\t"<<argv[3]<<endl;

		comb.comb();
	}

	return 0;
}

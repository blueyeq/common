#include <stdio.h>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <queue>
#include <fstream>

using namespace std;

const int max_node = 100000;
const int max_child = 26;
const int max_dis = 3;
const int max_len = 20;

int next[max_node][max_child], cost[max_node][max_child];
int  fail[max_node], leve[max_node];
char *substr[max_node / max_len];
int end[max_node / max_len];
bool vis[max_node * 10];  //  max_node * max_dis * max_len

int dis[max_node][max_dis];
int map[256];

typedef struct autoac{

	int line, ID;

	void init(){
		leve[0] = ID = line = 0;
		ID = 1;
		for(int i = 0; i < 26; ++i)  map[i + 'a'] = i;
	}

	int newnode(){
		if(ID >= max_node)  return -1;
		memset(next[ID], 0, sizeof(next[ID]));   // sizeof(int) * max_child
		memset(cost[ID], 0, sizeof(cost[ID]));   //  数目太多的话这一步可能会tle
		fail[ID] = 0;
		return ID++;
	}

	int insert(char *buf){  //  将 buf[] 插入查字典树中
		int p(0);
		printf("%s  ", buf);
		for(; *buf; ++buf){
			int value = map[*buf];
			if(!next[p][ value ])   {
				printf("%d %c\n", p, *buf);
				next[p][ value ] = newnode();
			}
			leve[next[p][ value ]] = leve[p] + 1;
			p = next[p][ value ];
		}
		printf("%d  %d\n",ID,  p);
		return p;
	}

	int bfs_make(){
		queue<int>  q_bfs;
		while(!q_bfs.empty())   q_bfs.pop();
		q_bfs.push(0);
		while(!q_bfs.empty()){
			int p = q_bfs.front();   q_bfs.pop();

			for(int i = 0; i < max_child; ++i){
				int child = next[p][i];
				if(!child){
					next[p][i] = next[fail[p]][i];
					cost[p][i] = leve[p] + 1 - leve[next[fail[p]][i]];
				}else {
					q_bfs.push(child);
					if(p)  fail[child] = next[fail[p]][i];
					else  fail[child] = 0;
				}
				//if(next[p][i]) printf("%d %d\n", p, next[p][i]);
			}
		}
		return 1;
	}

	int readin(char input[]){
		fstream fin(input, ios::in);
		
		if(!fin)  {
			printf("file input error!\n");
			return 0;
		}
		char buf[2048];
		line = 0;
		while(!fin.getline(buf, 2048).fail()){
			buf[max_len] = 0;
			int len = strlen(buf);
			substr[line] = (char *)  malloc( len + 1);
			strcpy(substr[line], buf);
			end[line++] = insert(buf);
		}
		return 1;
	}

	int get_state(int edit_dis, int pos_in_str, int pos_in_ac){ //  数据范围过大会溢出
		return edit_dis + pos_in_str * max_dis + pos_in_ac * max_dis * max_len;
	}

	int process(char *buf, int len){
		memset(vis, 0, sizeof(vis));   // 这里可以不用每次清空  但是vis为int 也就是每次的标记不同
		queue<int>  q;
		while(!q.empty())  q.pop();
		q.push(0);
		while(!q.empty()){
			int node = q.front();  q.pop();
			char edit_dis = node % max_dis;   node /= max_dis;
			char pos_in_str = node % max_len;   node /= max_len;
			int pos_in_ac = node;
			if(pos_in_str >= len || edit_dis >= max_dis )  continue;

			for(int i = 0; i < max_child; ++i){
				bool equal = map[ buf[pos_in_str] ] == i;

				int tmp_edit_dis = edit_dis + cost[pos_in_ac][i] + (!equal);
				if(tmp_edit_dis < max_dis){ // equal 则直接匹配 否则插入一个字符
				int new_node = get_state(tmp_edit_dis, pos_in_str + equal,  next[pos_in_ac][i] );
					if(!vis[new_node]){
						q.push(new_node);
						vis[new_node] = 1;
					//	printf("push insrt: %d  %d  %d\n",tmp_edit_dis, pos_in_str + equal, next[pos_in_ac][i]);
					}
				}
				if(edit_dis + 1 < max_dis ){ //实边才修改 否则不修改
					int new_node = get_state(edit_dis + 1, pos_in_str + 1, next[pos_in_ac][i]);  // 修改一个字符
					if(!vis[new_node]){
						q.push(new_node);
						vis[new_node] = 1;
					//	printf("push modify: %d  %d  %d\n",edit_dis + 1, pos_in_str + 1, next[pos_in_ac][i]);
					}
				}
			}
			if(edit_dis + 1 < max_dis){ //  删除一个字符
				int new_node = get_state(edit_dis + 1, pos_in_str + 1, pos_in_ac);
				if(!vis[new_node]){
					q.push(new_node);
					vis[new_node] = 1;
					//printf("push dele: %d  %d  %d\n",edit_dis + 1, pos_in_str + 1 , pos_in_ac);
				}
			}
		}
		return 1;
	}

	int get_ans(int len){
		
		int cnt(0);
		for(int i = 0; i < line; ++i){
			for(int j = 0; j < max_dis; ++j){
				int node = get_state(j, len , end[i]);
				if(vis[node]){
					printf("%d  %d: %s\n", i, j, substr[i]);
					++cnt;
					break;
				}
			}
		}
		printf("ans cnt:  %d\n", cnt);
		return 1;
	}

}AutoAc;

int main(){

	AutoAc queryFind;
	queryFind.init();
	char query[1000] = "woshizhongguoren";
	if(queryFind.readin("query.in")){
		queryFind.bfs_make();
		//while(scanf("%s", query) != EOF){
			queryFind.process(query, strlen(query));
			queryFind.get_ans(strlen(query));
		//}
	}
	for(int i = 0; i < queryFind.line; ++i){
		free( substr[i]);
	}
	return 0;
}

#ifndef AUTOAC_H
#define AUTOAC_H

#include <stdio.h>
#include <cstring>
#include <map>

struct tire_node{
	
	int M_size;
	int M_maxLen;
	bool M_isRealEnd;

	map<string, int> M_hash_char;
	tire_node *M_child_ptr;

	tire_node(){
		M_size = 0;
		M_maxLen = 0;
		M_isRealEnd = 0;
		M_child_ptr = NULL;
		hash_char.clear();
	}
	tire_node* add_child(char *p);
	tire_node* get_child(char *p);
	~tire_node(){
		map.clear();
		for(int i = 0; i < M_size; ++i){
			delete *M_child_ptr;
		}
	}
};

struct auto_ac{
	
	tire_node *root;
	bool insert_string(char *ptr);
	bool bfs_make();
	bool process();
	int  get_result();
	auto_ac(){
		root = NULL;
		root = (tire_node *) malloc(sizeof(tire_node)); 
	}
	
	




};

#endif

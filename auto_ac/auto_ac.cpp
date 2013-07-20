#include <stdio.h>
#include <cstring>
#include <autoac.h>


tire_node* tire_node::add_child(char *p){
	if(M_hash_char.find(p) == M_hash_char.end()){
		p[M_size] = (tire_node *) malloc(sizeof(tire_node));
		if(p[M_size] == NULL)  return false;
		M_hash_char[p] = M_size++;
	}
	return M_child_ptr[M_hash_char[*p]];
}

tire_node* tire_node::get_child(char *p){
	if(M_hash_char.find(p) == M_hash_char.end()){
		return add_child(*p);
	}else {
		return M_child_ptr[M_hash_char];
	}
}

inline bool isHead(char c){
	return c < 0;
}
inline bool isASCII(char c){
	return c > 0;
}
inline bool isTail(char c){
	return c < 0;
}
bool auto_ac::insert_string(char *ptr){
	char *word[5];
	tire_node *ptr_now = root;
	if(ptr_now == NULL) {
		return false;
	}
	for(; *ptr; ++ptr){
		int j(0);
		if(isHead(*ptr)){
			while(*ptr && !isTail(*ptr))  word[j++] = *ptr++;  
		}else if(isASCII(*ptr)){
			word[j] = *ptr++;
		}
		word[j++] = 0;
		ptr = get_child(word);
	}
}



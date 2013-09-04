#ifndef SEGMENTTREE_H
#define SEGMENTTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

namespace segmentTree{
template<class T>
class SegmentTree{
private:	
	struct node{
		  T		 key1;
		  T		 key2;
		short int pos1;
		short int pos2;
	};
	
	struct node* m_element;

	int			m_size;
	int			m_used;
	int			m_effective;
	int		   *m_pos_map;
	
	bool intPos();
	
public:
	bool initPos(int pos, int p_left, int p_right);
	bool init( int size);
	bool insert(int pos, bool need_map, const T &key);
	bool updateTop(T key);
	T   getKey1() ;
	T   getKey2() ;

	SegmentTree();
	~SegmentTree();

	void debug()
	{
		printf("pos1[%d]Min1", m_element[1].pos1);
		m_element[1].key1->print();
		printf("pos2[%d]Min2", m_element[1].pos2);
		m_element[1].key2->print();
	}

};


template<class T>
SegmentTree<T>::SegmentTree():
	m_element(NULL), m_size(0), m_used(0), m_effective(0)
{

}

template<class T>
SegmentTree<T>::~SegmentTree()
{
	if(m_element){
		free(m_element);
	}
	if(m_pos_map){
		free(m_pos_map);
	}
}

template<class T>
bool SegmentTree<T>::initPos(int pos, int p_left, int p_right)
{
	if(p_left == p_right){
		m_pos_map[p_left] = pos;
		return true;
	}
	if(p_left > p_right){
		fprintf(stderr, "ERROR: initPos failed\n");
		return false;
	}
	int mid((p_left + p_right) >> 1);
	return initPos(pos<<1, p_left, mid) && initPos((pos<<1) | 1, mid + 1, p_right);

}

template<class T>
bool SegmentTree<T>::init( int num_element)
{
	if(num_element > 0) {
		m_element = (node *) malloc( sizeof(node) * (num_element * 4 + 2));
		if(!m_element) {
			fprintf(stderr, "ERROR: malloc m_element failed\n");
			return false;
		}
		m_pos_map  = (int*) malloc(sizeof(int) * num_element + 2);
		if(!m_pos_map){
			fprintf(stderr, "ERROR: malloc m_pos_map failed\n");
			return false;
		}
		m_effective = num_element;
		m_size = num_element * 4;
		if(!initPos(1, 1, num_element)){
			free(m_element);
			free(m_pos_map);
			fprintf(stderr, "ERROR: initPos failed\n");
			return false;
		}
		for(int i = 1; i <= m_size; ++i){
			m_element[i].pos1 = m_element[i].pos2 = -1;
		}
	}
	return true;
}

template<class T>
inline T SegmentTree<T>::getKey1() 
{
	//if(m_element == NULL)  return NULL;
	return m_element[1].pos1 == -1 ? NULL: m_element[1].key1;
}

template<class T>
inline T SegmentTree<T>::getKey2() 
{
	//if(m_element == NULL) return NULL;
	return m_element[1].pos2 == -1 ? NULL: m_element[1].key2;
}

template<class T>
inline bool SegmentTree<T>::updateTop(T key)
{
	int pos = m_element[1].pos1;
	if( pos == -1) return true;
	return insert(pos, false, key);
}

template<class T> 
bool SegmentTree<T>::insert(int pos, bool need_map, const T &key)
{
	/*
	if(pos >= m_size || pos <= 0)  {
		fprintf(stderr, "ERROR: insert failed for pos[%d] > m_size[%d] ", pos, m_effective);
		return false;
	}
	*/
	if(need_map)  pos = m_pos_map[pos];

	m_element[pos].key1 = key;
	m_element[pos].pos1  = key == NULL ? -1 : pos;
	m_element[pos].pos2	 = -1;
	
	pos >>= 1;

	while( pos ){

		int lc = pos<<1;
		int rc = lc | 1;
		//if( true){ // 重载大于小于的时候堆中相反
		{
			if(m_element[lc].pos1 != -1 &&  (m_element[rc].pos1 == -1 || *m_element[rc].key1 < *m_element[lc].key1) ){

				m_element[pos].key1 = m_element[lc].key1;
				m_element[pos].pos1  = m_element[lc].pos1;
				if(m_element[lc].pos2 != -1 && ( m_element[rc].pos1 == -1 ||  *m_element[rc].key1 < *m_element[lc].key2  )){

					m_element[pos].key2 = m_element[lc].key2;
					m_element[pos].pos2  = m_element[lc].pos2;
				}else{

					m_element[pos].key2 = m_element[rc].key1;
					m_element[pos].pos2  = m_element[rc].pos1;
				}
			}else {

				m_element[pos].key1 = m_element[rc].key1;
				m_element[pos].pos1  = m_element[rc].pos1;
				if(m_element[rc].pos2 != -1 && ( m_element[lc].pos1 == -1 || *m_element[lc].key1 < *m_element[rc].key2  )){

					m_element[pos].key2 = m_element[rc].key2;
					m_element[pos].pos2  = m_element[rc].pos2;

				}else{

					m_element[pos].key2 = m_element[lc].key1;
					m_element[pos].pos2  = m_element[lc].pos1;
				}
			}
	//	}
		}

		pos >>= 1;
	}
	return true;
}

}

#endif

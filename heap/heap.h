#include <stdio.h>
#include <algorithm>

namespace util{

template<typename T, typename Compare>
class AdjustHeap{
  public:
    AdjustHeap():_size(0),_capatiy(0),_element(NULL)
    {
    }
    ~AdjustHeap()
    {
      if (_element) {
        delete[] _element;
        _element = NULL;
      }
    }
    bool init(int size);      //初始化容量
    T pop();                 //弹出堆顶
    void push(T a);          //超过容量会自动调用pop 
    void clear();             //清空size
    void setTopK(int32_t top_k); //topK的堆 <= _capatiy  默认_capatiy
    int32_t size();           //大小 
    bool empty();
    void print();
  private:
    void down(int n);
    void up(int n);
  private:
    Compare _cmp;
    int32_t _size;
    int32_t _capatiy;
    int32_t _top_k;
    T *_element;
};

template<typename T, typename Compare>
bool AdjustHeap<T,Compare>::init(int size)
{
  if(size < 1){
    return false;
  }
  _element = new T[size+1];
  if(!_element){
    return false;
  }
  _capatiy = size;
  _size = 0;
  _top_k = 0;
  return true;
}

template <typename T,typename Compare>
void AdjustHeap<T,Compare>::clear()
{
  //memset(_element,0,sizeof(T*)*(size+1));
  _size = 0;
  _top_k = 0;
}

template<typename T,typename Compare>
bool AdjustHeap<T,Compare>::empty()
{
  return _size < 1;
}

template<typename T,typename Compare>
int32_t AdjustHeap<T,Compare>::size()
{
  return _size;
}

template<typename T,typename Compare>
void AdjustHeap<T,Compare>::setTopK(int top_k)
{
  if (top_k > _capatiy) {
    top_k = _capatiy;
  }
  _top_k = top_k;
}



template<typename T, typename Compare>
void AdjustHeap<T,Compare>::push(T value)
{
  if (_size < _top_k){
    _element[++_size] = value;
    up(_size);
  }else if (_size > 0){ // _SIZE > 0;
    if (_cmp(value,_element[1])) {
      _element[1] = value;
      down(1);
    }
  }
}

template<typename T,typename Compare>
void AdjustHeap<T,Compare>::up(int n)
{
  if (n > _size) {
    return;
  }
  while (n > 1) {
    int fa = n>>1;
    if(_cmp(_element[fa],_element[n])){
      std::swap(_element[n],_element[fa]);
    }else{
      break;
    }
    n = fa;
  }
}

template<typename T,typename Compare>
void AdjustHeap<T,Compare>::down(int n)
{
  if (n < 1 || n > _size) {
    return;
  }
  T value = _element[n];
  while (n < _size) {
    int lc = n<<1;
    int rc = lc | 1;
    if (rc <= _size && _cmp(value,_element[rc])) {
      if (_cmp(_element[rc],_element[lc])) {
        _element[n] = _element[lc];
        n = lc;
      }else{
        _element[n] = _element[rc];
        n = rc;
      }
    }else if (lc <= _size && _cmp(value, _element[lc])) {
      _element[n] = _element[lc];
      n = lc;
    }else{
      break;
    }
  }
  _element[n] = value;
}

template<typename T,typename Compare>
T AdjustHeap<T,Compare>::pop()
{
  if(_size < 1){
    return NULL;
  }
  T res = _element[1];
  _element[1] = _element[_size--];
  if(_size > 1){
    down(1);
  }
  return res;
}

template<typename T,typename Compare>
void AdjustHeap<T,Compare>::print()
{
  printf("size[%d]: ",_size);
  for(int i = 1;i <= _size; ++i){
    printf("%d ",*_element[i]);
  }
  printf("\n");
}


};

/* sw=2;ts=2;sts=2;expandtab */

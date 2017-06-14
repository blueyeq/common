#include <stdio.h>

namespace util{
static const int BIT_MASK[] = {0,1,3,7,15,31,63,127,255,511,1023,2047,4095,8191,16383,32767};
struct BitsArray
{
  Bits(char* buf, uint64_t buf_size, int32_t bit_size)
  {
    _buf = buf;
    _buf_size = buf_size;
    _bit_size = bit_size;
  }

  int get(int id){
    char *ptr = buf + id*_bit_size / sizeof(char);
    int32_t high = *ptr & (BIT_MASK[sizeof(char) - id*_buf_size % sizeof(char)]);
    int32_t low = (*(ptr + 1)) & BIT_MASK[id*_buf_size % sizeof(char)]; 
    int32_t value = (high << sizeof(char) - id*_buf_size % sizeof(char) ) | low;
  }
  char *_buf;
  uint64_t _buf_size;
  int32_t _bit_size;
};
}
/* sw=2;ts=2;sts=2;expandtab */

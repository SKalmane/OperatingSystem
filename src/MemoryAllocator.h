#include <stdint.h>

struct block_header {
  uint8_t free : 1;
  uint8_t pid : 7;
  uint32_t bytes : 24;
  struct block_header *next_header;
  uint32_t data[0];
} header;

void *myMalloc(unsigned int size);

void myFree(void *ptr);

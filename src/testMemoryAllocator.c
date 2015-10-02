#include <stdio.h>

#include "MemoryAllocator.h"

int main() {
  int errCode = 0;
  errCode = testSizeOfBlockHeader();
  if(errCode) {
    fprintf(stderr, "Block header is not double word aligned\n");
    return errCode;
  }
  errCode = testMyMallocBasic();
  if(errCode) {
    return errCode;
  }
  return 0;
}

int testSizeOfBlockHeader() {
  long int size = sizeof(struct block_header);
  fprintf(stdout,
	  "===== Running test to check size of block header =====\n");
  

  fprintf(stdout, "Size of block_header: %ld bytes\n", size);
  fprintf(stdout, "======================================================\n");
  if(size % 8) {
    return -1;
  }
  return 0;
}

int testMyMallocBasic() {
  myMalloc(15);
  return 0;
}

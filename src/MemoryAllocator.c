// Library includes
#include <stdlib.h> // malloc
#include <stdio.h>  // fprintf
// Local includes
#include "MemoryAllocator.h"

#define FALSE 0
#define TRUE  1

#define KILO 1024
#define MEGA ((KILO) * (KILO))

static int firstMemoryAllocation = TRUE;

void *myMalloc(unsigned int size) {
  static void *entireBlockOfMemory;
  struct block_header *header_ptr;
  
  if(firstMemoryAllocation) {
    fprintf(stdout, "This is the first allocation\n");
    firstMemoryAllocation = FALSE;
    // Allocate 1 MB of space
    entireBlockOfMemory =
      (void *)(malloc(MEGA * sizeof(uint8_t)));
    header_ptr = ((struct block_header *)(entireBlockOfMemory));
    // Initialize the first header
    *header_ptr = header;
    header_ptr->free  = TRUE;
    header_ptr->bytes =  (MEGA * sizeof(uint8_t)) -
      sizeof(struct block_header);
    header_ptr->next_header = NULL;
    fprintf(stdout, "Header Pointer is: %p\n", (header_ptr));
    fprintf(stdout, "Data starts at: %p\n", (header_ptr->data));
  }
  header_ptr = ((struct block_header *)(entireBlockOfMemory));
  while(!(header_ptr->free)) {
    header_ptr = (struct block_header *)(header_ptr->data + header_ptr->bytes);
  }
  fprintf(stdout, "Header Pointer is: %p\n", (header_ptr));
  header_ptr->free = FALSE;
  header_ptr->pid  = 0;
  header_ptr->bytes = (uint32_t)((size + 7) & ~7);
  header_ptr->next_header = (struct block_header *)(header_ptr->data + (uint32_t)(header_ptr->bytes));
  fprintf(stdout, "Next Header Pointer is: %p\n", (header_ptr->next_header));
  *(header_ptr->next_header) = header;
  fprintf(stdout, "Next Header free? : %d\n", (header_ptr->next_header->free));
  if(size == 0) {
    return NULL;
  }
  
}

void myFree(void *ptr) {

}

/* int main() { */
  
/*   return 0; */
/* } */

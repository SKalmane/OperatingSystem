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

void setHeaderData(struct block_header *header,
		   uint8_t free,
		   uint8_t pid,
		   uint32_t freeBytes,
		   struct block_header *next_header) {
  header->free = free;
  header->pid = pid;
  header->bytes = freeBytes;
  header->next_header = next_header;
}

void initializeHeaderData(struct block_header *header,
			  uint32_t freeBytes,
			  struct block_header *next_header) {
  setHeaderData(header, TRUE, 0, freeBytes, next_header);
}

void *myMalloc(unsigned int size) {
  static void *entireBlockOfMemory;
  struct block_header *header_ptr;
  uint32_t free_bytes;
  struct block_header *next_header;
  struct block_header new_header;

  if(size == 0) {
    return NULL;
  }
  if(firstMemoryAllocation) {
    fprintf(stdout, "This is the first allocation\n");
    firstMemoryAllocation = FALSE;
    // Allocate 1 MB of space
    entireBlockOfMemory =
      (void *)(malloc(MEGA * sizeof(uint8_t)));
    header_ptr = ((struct block_header *)(entireBlockOfMemory));
    // Initialize the first header
    *header_ptr = header;
    initializeHeaderData(header_ptr,
			 (uint32_t)((MEGA * sizeof(uint8_t)) -
				    sizeof(struct block_header)),
			 NULL);
    fprintf(stdout, "Header Pointer is: %p\n", (header_ptr));
    fprintf(stdout, "Data starts at: %p\n", (header_ptr->data));
  }
  header_ptr = ((struct block_header *)(entireBlockOfMemory));
  while(!(header_ptr->free)) {
    header_ptr = (struct block_header *)(header_ptr->data + header_ptr->bytes);
  }
  fprintf(stdout, "Header Pointer is: %p\n", (header_ptr));
  free_bytes = header_ptr->bytes;
  setHeaderData(header_ptr, FALSE, 0,
		(uint32_t)((size + 7) & ~7),
		(struct block_header *)(header_ptr->data + (uint32_t)((size + 7) & ~7)));
  fprintf(stdout, "Size allocated is: %d\n", ((size + 7) & ~7)); 
  fprintf(stdout, "Next Header Pointer is: %p\n", (header_ptr->next_header));
  next_header = header_ptr->next_header;
  (*next_header) = header;
  header_ptr->next_header->free = TRUE;
  initializeHeaderData(header_ptr->next_header,
		       free_bytes - sizeof(struct block_header),
		       next_header);
  fprintf(stdout, "Next Header free? : %d\n", (header_ptr->next_header->free));  
}

void myFree(void *ptr) {

}

/* int main() { */
  
/*   return 0; */
/* } */

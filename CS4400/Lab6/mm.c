/*
 * Tim Dorny u0829896 naive implementation v1.1
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/* always use 16-byte alignment */
#define ALIGNMENT 16

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~(ALIGNMENT-1))

/* rounds up to the nearest multiple of mem_pagesize() */
#define PAGE_ALIGN(size) (((size) + (mem_pagesize()-1)) & ~(mem_pagesize()-1))

// Get header from payload pointer
#define HDRP(bp) ((char *)(bp) - sizeof(block_header))
// Get size of block from pointer to header
#define GET_SIZE(p) ((block_header *)(p))->size
// Check if a block is allocated given its header
#define GET_ISALLOC(p) ((block_header *)(p))->isAlloc
// Calculates overhead required for header
#define OVERHEAD sizeof(block_header)

void *current_avail = NULL;
int current_avail_size = 0;
typedef struct {
  size_t size;
  char isAlloc;
} block_header;

/* 
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
  current_avail = NULL;
  current_avail_size = 0;
  
  return 0;
}

/* 
 * mm_malloc - Allocate a block by using bytes from current_avail,
 *     grabbing a new page if necessary.
 */
void *mm_malloc(size_t size)
{
  // Compensate for overhead
  int newsize = ALIGN(size + OVERHEAD);
  void *p;
  
  if (current_avail_size < newsize) {
    current_avail_size = PAGE_ALIGN(newsize);
    current_avail = mem_map(current_avail_size);
    if (current_avail == NULL)
      return NULL;
  }

  p = current_avail;
  current_avail += newsize;
  current_avail_size -= newsize;
  
  return p;
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
  size_t size = GET_SIZE(HDRP(ptr));
  char alloc = GET_ISALLOC(HDRP(ptr));
  if (alloc){
    GET_ISALLOC(HDRP(ptr)) = 0;
    mem_unmap(ptr, size);
    }
}

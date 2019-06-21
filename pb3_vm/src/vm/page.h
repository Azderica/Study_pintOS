#ifndef VM_PAGE_H
#define VM_PAGE_H

#include <hash.h>
#include "devices/block.h"
#include "filesys/off_t.h"
#include "threads/synch.h"

/* Virtual page. */
struct page
{
  void *addr;    // user virtual address 
  bool read_only;     // check read-only
  struct thread *thread; // owing thread

  struct hash_elem hash_elem; // my haseed pages

  struct frame *frame;  // page frame

  block_sector_t sector; // for sector 

  bool private;     
  struct file *file; // file
  off_t file_offset; // offset in file
  off_t file_bytes;  // bytes in file
};

void page_exit(void);

struct page *page_allocate(void *, bool read_only);
void page_deallocate(void *vaddr);

bool page_in(void *fault_addr);
bool page_out(struct page *);
bool page_accessed_recently(struct page *);

bool page_lock(const void *, bool will_write);
void page_unlock(const void *);

hash_hash_func page_hash;
hash_less_func page_less;

#endif
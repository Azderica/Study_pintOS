#ifndef VM_SWAP_H
#define VM_SWAP_H 1

#include <stdbool.h>

struct page;
void swap_init (void);          // swap init
void swap_in (struct page *);   // swap in
bool swap_out (struct page *);  // swap out

#endif

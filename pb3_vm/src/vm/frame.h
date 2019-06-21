#ifndef VM_FRAME_H
#define VM_FRAME_H

#include <stdbool.h>
#include "threads/synch.h"

/* A physical frame. */
struct frame
{
  struct lock lock;  /* Prevent simultaneous access. */
  void *base;        /* Kernel virtual base address. */
  struct page *page; /* Mapped process page, if any. */
};

void frame_init(void); // init frame

struct frame *frame_alloc_and_lock(struct page *); // frame alloc and lock
void frame_lock(struct page *); // frame lock
void frame_free(struct frame *); // frame free
void frame_unlock(struct frame *); // frame unlock

#endif

#ifndef SLAB_H
#define SLAB_H

#include <stddef.h>
#include <stdint.h>
#include "cnabl/ls.h"

struct slab_alloc {
  struct ls slabs, free_slots;
  size_t slot_count, slot_size, i;
};

struct slab_alloc *slab_init(struct slab_alloc *alloc, size_t slot_count, size_t slot_size);
struct slab_alloc *slab_deinit(struct slab_alloc *alloc);

void *slab_malloc(struct slab_alloc *alloc);
void slab_free(struct slab_alloc *alloc, void *p);
  
#endif

#include <stdlib.h>
#include "cnabl/slab.h"

struct slab_slot {
  struct ls ls;
  uint8_t data[];
};

struct slab {
  struct ls ls;
  uint8_t slots[];
};

struct slab_alloc *slab_init(struct slab_alloc *alloc, size_t slot_count, size_t slot_size) {
  ls_init(&alloc->slabs);
  ls_init(&alloc->free_slots);
  alloc->slot_count = slot_count;
  alloc->slot_size = slot_size;
  alloc->i = slot_count;
  return alloc;
}

struct slab_alloc *slab_deinit(struct slab_alloc *alloc) {
  ls_do(&alloc->slabs, slab_ls) {
    struct slab *s = cl_baseof(slab_ls, struct slab, ls);
    free(s);
  }

  return alloc;
}

static struct slab *slab_get(struct slab_alloc *alloc) {
  if (alloc->i == alloc->slot_count) {
    struct slab *s = malloc(sizeof(struct slab) +
			    cl_align((sizeof(struct slab_slot) + alloc->slot_size), sizeof(struct slab_slot)) *
			    alloc->slot_count);
    ls_push_back(&alloc->slabs, &s->ls);
    alloc->i = 0;
    return s;
  }

  return cl_baseof(alloc->slabs.prev, struct slab, ls);
}

void *slab_malloc(struct slab_alloc *alloc) {
  struct ls *slot_ls = alloc->free_slots.prev;

  if (slot_ls == &alloc->free_slots) {
    slot_ls = (struct ls *)cl_align(slab_get(alloc)->slots +
				    alloc->i++ * (sizeof(struct slab_slot) + alloc->slot_size),
				    sizeof(struct slab_slot));
  } else {
    ls_remove(slot_ls);
  }
  
  return cl_baseof(slot_ls, struct slab_slot, ls)->data;
}

void slab_free(struct slab_alloc *alloc, void *p) {
  ls_push_back(&alloc->free_slots, &cl_baseof(p, struct slab_slot, data)->ls);
}

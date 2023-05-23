#include <stdlib.h>
#include "cnabl/slab.h"

struct slab {
  struct ls ls;
  uint8_t slots[];
};

struct slab_alloc *slab_init(struct slab_alloc *alloc, size_t slot_count, size_t slot_size) {
  ls_init(&alloc->slabs);
  vec_init(&alloc->free_slots, sizeof(uint8_t *));
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

  vec_deinit(&alloc->free_slots);
  return alloc;
}

static struct slab *slab_get(struct slab_alloc *alloc) {
  if (alloc->i == alloc->slot_count) {
    struct slab *s = malloc(sizeof(struct slab) + alloc->slot_size * alloc->slot_count);
    ls_push_back(&alloc->slabs, &s->ls);
    alloc->i = 0;
    return s;
  }

  return cl_baseof(alloc->slabs.prev, struct slab, ls);
}

void *slab_malloc(struct slab_alloc *alloc) {
  return alloc->free_slots.len
    ? *(uint8_t **)vec_pop(&alloc->free_slots)
    : slab_get(alloc)->slots + alloc->i++ * alloc->slot_size;
}

void slab_free(struct slab_alloc *alloc, void *p) {
  *(uint8_t **)vec_push(&alloc->free_slots) = p;
}

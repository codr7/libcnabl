#include <stdlib.h>
#include <string.h>

#include "cnabl/vec.h"

struct vec *vec_init(struct vec *vec, size_t item_size) {
  vec->item_size = item_size;
  vec->cap = vec->len = 0;
  vec->items = vec->start = vec->end = NULL;
  return vec;
}

void vec_deinit(struct vec *vec) {
  if (vec->items) {
    free(vec->items);
  }
}

void vec_grow(struct vec *vec, size_t cap) {
  vec->cap = cap ? cap : 2;
  vec->items = realloc(vec->items, vec->item_size*(vec->cap+1));
  vec->start = cl_align(vec->items, vec->item_size);
  vec->end = vec->start + vec->item_size*vec->len;
}

void vec_clear(struct vec *vec) {
  vec->len = 0;
  vec->end = vec->start;
}

void *vec_get(struct vec *vec, size_t i) {
  return vec->items ? vec->start + vec->item_size*i : NULL;
}

void *vec_push(struct vec *vec) {
  if (vec->len == vec->cap) {
    vec_grow(vec, vec->cap*2);
  }

  void *p = vec->end;
  vec->end += vec->item_size;
  vec->len++;
  return p;
}

void *vec_peek(struct vec *vec) {
  return vec->len ? vec->end - vec->item_size : NULL;
}

void *vec_pop(struct vec *vec) {
  if (!vec->len) {
    return NULL;
  }

  vec->end -= vec->item_size;
  vec->len--;
  return vec->end;
}

void *vec_insert(struct vec *vec, size_t i) {
  if (vec->len == vec->cap) {
    vec_grow(vec, vec->cap*2);
  } 

  uint8_t *const p = vec_get(vec, i);
  memmove(p+vec->item_size, p, (vec->len-i)*vec->item_size);
  vec->len++;
  vec->end += vec->item_size;
  return p;
}

bool vec_delete(struct vec *vec, size_t i, size_t n) {
  if (vec->len < i+n) {
    return false;
  }

  if (i+n < vec->len) {
    uint8_t *const p = vec_get(vec, i);
    size_t s = vec->item_size*n;
    memmove(p, p + s, s);
  }

  vec->len -= n;
  vec->end -= n*vec->item_size;
  return true;
}

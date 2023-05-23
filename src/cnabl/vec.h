#ifndef VEC_H
#define VEC_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "cnabl/macros.h"

#define _vec_do(_vec, _type, var, _i)		\
  size_t _i = 0;				\
  for (_type var = (_type)(_vec)->start;	\
       _i < (_vec)->len;			\
       _i++, var++)

#define vec_do(_vec, _type, var)		\
  _vec_do(_vec, _type, var, cl_unique(i))

struct vec {
  size_t item_size, cap, len;
  uint8_t *items, *start, *end;
};

struct vec *vec_init(struct vec *vec, size_t size);
void vec_deinit(struct vec *vec);
void vec_grow(struct vec *vec, size_t cap);
void vec_clear(struct vec *vec);
void *vec_get(struct vec *vec, size_t i);
void *vec_push(struct vec *vec);
void *vec_peek(struct vec *vec);
void *vec_pop(struct vec *vec);
void *vec_insert(struct vec *vec, size_t i);
bool vec_delete(struct vec *vec, size_t i, size_t n);

#endif

#ifndef LS_H
#define LS_H

#include "cnabl/macros.h"

#define _ls_do(_ls, i, _next)				\
  for (struct ls *i = (_ls)->next, *_next = i->next;	\
       i != (_ls);					\
       i = _next, _next = i->next)

#define ls_do(_ls, i)				\
  _ls_do(_ls, i, cl_unique(next))

struct ls {
  struct ls *prev, *next;
};

void ls_init(struct ls *ls);

void ls_insert(struct ls *ls, struct ls *item);
struct ls *ls_remove(struct ls *ls);

void ls_push_front(struct ls *ls, struct ls *item);
struct ls *ls_pop_front(struct ls *ls);

void ls_push_back(struct ls *ls, struct ls *item);
struct ls *ls_pop_back(struct ls *ls);

#endif

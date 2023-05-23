#include <stddef.h>
#include "cnabl/ls.h"

void ls_init(struct ls *ls) {
  ls->prev = ls->next = ls;
}

void ls_insert(struct ls *ls, struct ls *item) {
  item->prev = ls->prev;
  ls->prev->next = item;
  item->next = ls;
  ls->prev = item;
}

struct ls *ls_remove(struct ls *ls) {
  ls->prev->next = ls->next;
  ls->next->prev = ls->prev;
  return ls;
}

void ls_push_front(struct ls *ls, struct ls *item) {
  ls_insert(ls->next, item);
}

struct ls *ls_pop_front(struct ls *ls) {
  struct ls *i = ls->next;
  return (i == ls) ? NULL : ls_remove(i);
}

void ls_push_back(struct ls *ls, struct ls *item) {
  ls_insert(ls, item);
}

struct ls *ls_pop_back(struct ls *ls) {
  struct ls *i = ls->prev;
  return (i == ls) ? NULL : ls_remove(i);
}

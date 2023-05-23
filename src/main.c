#include <assert.h>
#include <stdlib.h>
#include "cnabl/slab.h"

#define MAX 10000000
int *ps[MAX];

int main() {
  struct slab_alloc a;
  slab_init(&a, 10, sizeof(int));
  int *p1 = slab_malloc(&a);
  int *p2 = slab_malloc(&a);
  slab_free(&a, p1);
  slab_free(&a, p2);
  int *p3 = slab_malloc(&a);
  assert(p3 == p2);
  p3 = slab_malloc(&a);
  assert(p3 == p1);

  for (int i = 0; i < MAX; i++) {
    ps[i] = malloc(sizeof(int));
    *ps[i] = i;
  }

  for (int i = 0; i < MAX; i++) {
    free(ps[i]);
  }

  for (int i = 0; i < MAX; i++) {
    ps[i] = slab_malloc(&a);
    *ps[i] = i;
  }

  for (int i = 0; i < MAX; i++) {
    slab_free(&a, ps[i]);
  }

  slab_deinit(&a);
}

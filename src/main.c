#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "cnabl/slab.h"
#include "cnabl/timer.h"

#define MAX 10000000
int *ps[MAX];

int main() {
  struct slab_alloc a;
  slab_init(&a, 64, sizeof(int));
  int *p1 = slab_malloc(&a);
  int *p2 = slab_malloc(&a);
  slab_free(&a, p1);
  slab_free(&a, p2);
  int *p3 = slab_malloc(&a);
  assert(p3 == p2);
  p3 = slab_malloc(&a);
  assert(p3 == p1);

  struct timer t;
  timer_reset(&t);
  
  for (int i = 0; i < MAX; i++) {
    ps[i] = malloc(sizeof(int));
    *ps[i] = i;
  }

  for (int i = 0; i < MAX; i++) {
    free(ps[i]);
  }

  printf("%" PRIu64 "ns\n", timer_nsecs(&t));
  timer_reset(&t);
  
  for (int i = 0; i < MAX; i++) {
    ps[i] = slab_malloc(&a);
    *ps[i] = i;
  }

  for (int i = 0; i < MAX; i++) {
    slab_free(&a, ps[i]);
  }

  printf("%" PRIu64 "ns\n", timer_nsecs(&t));
  slab_deinit(&a);
}

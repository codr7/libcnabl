#include <errno.h>
#include "cnabl/fail.h"
#include "cnabl/timer.h"

void timer_reset(struct timer *self) {
  if (!timespec_get(&self->start, TIME_UTC)) {
    cl_fail("Failed getting time: %d", errno);
  }
}

uint64_t timer_nsecs(const struct timer *self) {
  struct timespec end;
  
  if (!timespec_get(&end, TIME_UTC)) {
    cl_fail("Failed getting time: %d", errno);
    return 0;
  }
  
  return
    (end.tv_sec - self->start.tv_sec) * 1000000000 +
    (end.tv_nsec - self->start.tv_nsec);
}


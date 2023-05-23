#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <time.h>

struct timer {
  struct timespec start;
};

void timer_reset(struct timer *self);
uint64_t timer_nsecs(const struct timer *self);

#endif

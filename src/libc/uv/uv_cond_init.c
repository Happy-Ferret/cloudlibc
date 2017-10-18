// Copyright (c) 2017 Nuxi, https://nuxi.nl/
//
// This file is distributed under a 2-clause BSD license.
// See the LICENSE file for details.

#include <pthread.h>
#include <uv.h>

int uv_cond_init(uv_cond_t *cond) {
  pthread_condattr_t attr;
  int error = pthread_condattr_init(&attr);
  if (error != 0)
    return -error;
  error = pthread_condattr_setclock(&attr, CLOCK_MONOTONIC);
  if (error != 0) {
    pthread_condattr_destroy(&attr);
    return -error;
  }
  error = pthread_cond_init(cond, &attr);
  pthread_condattr_destroy(&attr);
  return -error;
}

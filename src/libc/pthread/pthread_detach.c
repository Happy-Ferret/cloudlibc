// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distributed under a 2-clause BSD license.
// See the LICENSE file for details.

#include <common/crt.h>

#include <assert.h>
#include <pthread.h>
#include <stdatomic.h>

int pthread_detach(pthread_t thread) {
  if (refcount_release(&thread->refcount)) {
    // Thread has already passed the point that allows us to detach.
    // Join the thread itself to ensure the thread's resources are
    // cleaned up.
    return pthread_join(thread, NULL);
  }
  return 0;
}

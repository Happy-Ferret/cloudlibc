// Copyright (c) 2017 Nuxi, https://nuxi.nl/
//
// This file is distributed under a 2-clause BSD license.
// See the LICENSE file for details.

#include <semaphore.h>
#include <stdlib.h>
#include <uv.h>

void uv_sem_post(uv_sem_t *sem) {
  if (sem_post(sem) != 0)
    abort();
}

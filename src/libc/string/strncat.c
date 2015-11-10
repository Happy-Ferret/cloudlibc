// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#define _CLOUDLIBC_UNSAFE_STRING_FUNCTIONS

#include <string.h>

char *strncat(char *restrict s1, const char *restrict s2, size_t n) {
  if (n > 0) {
    char *s = s1;
    while (*s != L'\0')
      ++s;
    do {
      *s++ = *s2;
      if (*s2++ == L'\0')
        break;
    } while (--n > 0);
  }
  return s1;
}
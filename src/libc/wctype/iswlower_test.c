// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// SPDX-License-Identifier: BSD-2-Clause

#include <testing.h>
#include <wctype.h>

TEST(iswlower, equality) {
  for (wint_t wc = 0; wc <= 0x10ffff; ++wc) {
    SCOPED_NOTE(wc, { ASSERT_EQ(wc != towupper(wc), iswlower(wc)); });
  }
}

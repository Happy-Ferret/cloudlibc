// Copyright (c) 2017 Nuxi, https://nuxi.nl/
//
// SPDX-License-Identifier: BSD-2-Clause

#include <testing.h>
#include <uv.h>

TEST(uv_version, example) {
  // This implementation should be compatible with libuv 1.18.0.
  ASSERT_EQ(1 << 16 | 18 << 8 | 0, uv_version());
}

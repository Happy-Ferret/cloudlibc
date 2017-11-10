// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// SPDX-License-Identifier: BSD-2-Clause

#include <errno.h>
#include <testing.h>
#include <unistd.h>

TEST(symlinkat, bad) {
  // Bad directory file descriptor.
  ASSERT_EQ(-1, symlinkat("hello", 0xdeadc0de, "World"));
  ASSERT_EQ(EBADF, errno);

  // Empty pathname string.
  ASSERT_EQ(-1, symlinkat("hello", fd_tmp, ""));
  ASSERT_EQ(ENOENT, errno);
}

TEST(symlinkat, example) {
  ASSERT_EQ(0, symlinkat("Hello, world", fd_tmp, "foo"));
}

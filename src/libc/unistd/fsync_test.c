// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// SPDX-License-Identifier: BSD-2-Clause

#include <errno.h>
#include <fcntl.h>
#include <testing.h>
#include <unistd.h>

TEST(fsync, bad) {
  ASSERT_EQ(-1, fsync(-123));
  ASSERT_EQ(EBADF, errno);

  int fds[2];
  ASSERT_EQ(0, pipe(fds));
  ASSERT_EQ(-1, fsync(fds[0]));
  ASSERT_EQ(EINVAL, errno);
  ASSERT_EQ(0, close(fds[0]));
  ASSERT_EQ(0, close(fds[1]));
}

TEST(fsync, example) {
  int fd = openat(fd_tmp, "file", O_CREAT | O_RDWR);
  ASSERT_LE(0, fd);
  ASSERT_EQ(0, fsync(fd));
  ASSERT_EQ(0, close(fd));
}

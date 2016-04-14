// Copyright (c) 2015-2016 Nuxi, https://nuxi.nl/
//
// This file is distributed under a 2-clause BSD license.
// See the LICENSE file for details.

#include <sys/stat.h>

#include <fcntl.h>
#include <testing.h>
#include <unistd.h>

#define TIME_PASSED 1416225136

// File systems like HFS+ only provide one-second timestamp granularity.
// Also allow tv_nsec to remain zero.
#define TIMESPEC_EQ(sec, nsec, ts)                            \
  do {                                                        \
    ASSERT_EQ(sec, (ts).tv_sec);                              \
    ASSERT_TRUE((ts).tv_nsec == (nsec) || (ts).tv_nsec == 0); \
  } while (0);

TEST(utimensat, example) {
  // Create a FIFO and a symlink pointing to it.
  ASSERT_EQ(0, symlinkat("fifo", fd_tmp, "symlink"));
  ASSERT_EQ(0, mkfifoat(fd_tmp, "fifo"));

  // Set timestamps to known initial values.
  {
    struct timespec times[2] = {{.tv_sec = 345, .tv_nsec = 678},
                                {.tv_sec = 901, .tv_nsec = 234}};
    ASSERT_EQ(0, utimensat(fd_tmp, "symlink", times, 0));
  }
  {
    struct timespec times[2] = {{.tv_sec = 123, .tv_nsec = 456},
                                {.tv_sec = 234, .tv_nsec = 567}};
    ASSERT_EQ(0, utimensat(fd_tmp, "symlink", times, AT_SYMLINK_NOFOLLOW));
  }

  // Validate filetypes and timestamps before continuing.
  struct stat sb;
  ASSERT_EQ(0, fstatat(fd_tmp, "symlink", &sb, AT_SYMLINK_NOFOLLOW));
  ASSERT_TRUE(S_ISLNK(sb.st_mode));
  TIMESPEC_EQ(123, 456, sb.st_atim);
  TIMESPEC_EQ(234, 567, sb.st_mtim);

  ASSERT_EQ(0, fstatat(fd_tmp, "fifo", &sb, 0));
  ASSERT_TRUE(S_ISFIFO(sb.st_mode));
  TIMESPEC_EQ(345, 678, sb.st_atim);
  TIMESPEC_EQ(901, 234, sb.st_mtim);

  // UTIME_OMIT.
  {
    struct timespec times[2] = {{.tv_sec = 777, .tv_nsec = 888},
                                {.tv_nsec = UTIME_OMIT}};
    ASSERT_EQ(0, utimensat(fd_tmp, "symlink", times, AT_SYMLINK_NOFOLLOW));
  }
  {
    struct timespec times[2] = {{.tv_nsec = UTIME_OMIT},
                                {.tv_sec = 555, .tv_nsec = 666}};
    ASSERT_EQ(0, utimensat(fd_tmp, "fifo", times, 0));
  }

  ASSERT_EQ(0, fstatat(fd_tmp, "symlink", &sb, AT_SYMLINK_NOFOLLOW));
  TIMESPEC_EQ(777, 888, sb.st_atim);
  TIMESPEC_EQ(234, 567, sb.st_mtim);

  ASSERT_EQ(0, fstatat(fd_tmp, "fifo", &sb, 0));
  TIMESPEC_EQ(345, 678, sb.st_atim);
  TIMESPEC_EQ(555, 666, sb.st_mtim);

  // UTIME_NOW.
  {
    struct timespec times[2] = {{.tv_nsec = UTIME_OMIT},
                                {.tv_nsec = UTIME_NOW}};
    ASSERT_EQ(0, utimensat(fd_tmp, "symlink", times, AT_SYMLINK_NOFOLLOW));
  }
  {
    struct timespec times[2] = {{.tv_nsec = UTIME_NOW},
                                {.tv_nsec = UTIME_OMIT}};
    ASSERT_EQ(0, utimensat(fd_tmp, "fifo", times, 0));
  }

  ASSERT_EQ(0, fstatat(fd_tmp, "symlink", &sb, AT_SYMLINK_NOFOLLOW));
  TIMESPEC_EQ(777, 888, sb.st_atim);
  ASSERT_LE(TIME_PASSED, sb.st_mtime);

  ASSERT_EQ(0, fstatat(fd_tmp, "fifo", &sb, 0));
  ASSERT_LE(TIME_PASSED, sb.st_atime);
  TIMESPEC_EQ(555, 666, sb.st_mtim);

  // Null pointer.
  ASSERT_EQ(0, utimensat(fd_tmp, "symlink", NULL, AT_SYMLINK_NOFOLLOW));
  ASSERT_EQ(0, utimensat(fd_tmp, "fifo", NULL, 0));

  ASSERT_EQ(0, fstatat(fd_tmp, "symlink", &sb, AT_SYMLINK_NOFOLLOW));
  ASSERT_LE(TIME_PASSED, sb.st_atime);
  ASSERT_LE(TIME_PASSED, sb.st_mtime);

  ASSERT_EQ(0, fstatat(fd_tmp, "fifo", &sb, 0));
  ASSERT_LE(TIME_PASSED, sb.st_atime);
  ASSERT_LE(TIME_PASSED, sb.st_mtime);
}

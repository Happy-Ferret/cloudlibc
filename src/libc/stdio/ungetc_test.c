// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#include <errno.h>
#include <stdio.h>
#include <testing.h>
#include <unistd.h>

TEST(ungetc, ebadf) {
  // Create a stream to write side of a pipe.
  int fds[2];
  ASSERT_EQ(0, pipe(fds));
  FILE *fp = fdopen(fds[1], "w");

  // Pushing characters into the read buffer should not be permitted.
  ASSERT_EQ(EOF, ungetc('a', fp));
  ASSERT_FALSE(ferror(fp));
  ASSERT_EQ(EBADF, errno);

  ASSERT_EQ(0, fclose(fp));
  ASSERT_EQ(0, close(fds[0]));
}

TEST(ungetc, einval) {
  // Pushing EOF should leave the stream unchanged.
  ASSERT_EQ(EOF, ungetc(EOF, NULL));
  ASSERT_EQ(EINVAL, errno);
}

TEST(ungetc, enospc) {
  FILE *fp = tmpfile();
  ASSERT_NE(NULL, fp);

  // Push back characters until it fails.
  int ret;
  for (;;) {
    ret = ungetc('a', fp);
    if (ret == EOF)
      break;
    ASSERT_EQ('a', ret);
  }

  // Final push should have failed with ENOSPC.
  ASSERT_EQ(EOF, ret);
  ASSERT_FALSE(ferror(fp));
  ASSERT_EQ(ENOSPC, errno);

  ASSERT_EQ(0, fclose(fp));
}

TEST(ungetc, success) {
  FILE *fp = tmpfile();
  ASSERT_NE(NULL, fp);
  ASSERT_EQ('a', ungetc('a', fp));
  ASSERT_EQ('a', getc(fp));
  ASSERT_EQ(EOF, getc(fp));
  ASSERT_EQ(0, fclose(fp));
}

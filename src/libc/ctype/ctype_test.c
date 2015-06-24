// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <wctype.h>

#include <testing.h>

TEST(ctype, eof) {
  // EOF should match anything.
  ASSERT_EQ(0, isalnum(EOF));
  ASSERT_EQ(0, isalpha(EOF));
  ASSERT_FALSE(isascii(EOF));
  ASSERT_EQ(0, isblank(EOF));
  ASSERT_EQ(0, iscntrl(EOF));
  ASSERT_EQ(0, isdigit(EOF));
  ASSERT_EQ(0, isgraph(EOF));
  ASSERT_EQ(0, islower(EOF));
  ASSERT_EQ(0, isprint(EOF));
  ASSERT_EQ(0, ispunct(EOF));
  ASSERT_EQ(0, isspace(EOF));
  ASSERT_EQ(0, isupper(EOF));
  ASSERT_EQ(0, isxdigit(EOF));
  ASSERT_EQ(EOF, tolower(EOF));
  ASSERT_EQ(EOF, toupper(EOF));
}

TEST(ctype, ascii_to_wchar) {
  // All ASCII values should behave identically to the wide-character
  // counterparts.
  for (int ch = 0; ch <= 127; ++ch) {
    SCOPED_NOTE(ch, {
      ASSERT_EQ(iswalnum(ch), isalnum(ch));
      ASSERT_EQ(iswalpha(ch), isalpha(ch));
      ASSERT_TRUE(isascii(ch));
      ASSERT_EQ(iswblank(ch), isblank(ch));
      ASSERT_EQ(iswcntrl(ch), iscntrl(ch));
      ASSERT_EQ(iswdigit(ch), isdigit(ch));
      ASSERT_EQ(iswgraph(ch), isgraph(ch));
      ASSERT_EQ(iswlower(ch), islower(ch));
      ASSERT_EQ(iswprint(ch), isprint(ch));
      ASSERT_EQ(iswpunct(ch), ispunct(ch));
      ASSERT_EQ(iswspace(ch), isspace(ch));
      ASSERT_EQ(iswupper(ch), isupper(ch));
      ASSERT_EQ(iswxdigit(ch), isxdigit(ch));
      ASSERT_EQ(towlower(ch), tolower(ch));
      ASSERT_EQ(towupper(ch), toupper(ch));
    });
  }

  // Everything outside of ASCII should be invalid.
  for (int ch = 128; ch <= 255; ++ch) {
    SCOPED_NOTE(ch, {
      ASSERT_EQ(0, isalnum(ch));
      ASSERT_EQ(0, isalpha(ch));
      ASSERT_FALSE(isascii(ch));
      ASSERT_EQ(0, isblank(ch));
      ASSERT_EQ(0, iscntrl(ch));
      ASSERT_EQ(0, isdigit(ch));
      ASSERT_EQ(0, isgraph(ch));
      ASSERT_EQ(0, islower(ch));
      ASSERT_EQ(0, isprint(ch));
      ASSERT_EQ(0, ispunct(ch));
      ASSERT_EQ(0, isspace(ch));
      ASSERT_EQ(0, isupper(ch));
      ASSERT_EQ(0, isxdigit(ch));
      ASSERT_EQ(ch, tolower(ch));
      ASSERT_EQ(ch, toupper(ch));
    });
  }
}

TEST(ctype, ascii_equality) {
  // The _l() functions should behave identically to the plain versions
  // in case the C locale is used.
  for (int ch = -1024; ch < 1024; ++ch) {
    SCOPED_NOTE(ch, {
      ASSERT_EQ(isalnum(ch), isalnum_l(ch, LC_C_LOCALE));
      ASSERT_EQ(isalpha(ch), isalpha_l(ch, LC_C_LOCALE));
      ASSERT_EQ(isblank(ch), isblank_l(ch, LC_C_LOCALE));
      ASSERT_EQ(iscntrl(ch), iscntrl_l(ch, LC_C_LOCALE));
      ASSERT_EQ(isdigit(ch), isdigit_l(ch, LC_C_LOCALE));
      ASSERT_EQ(isgraph(ch), isgraph_l(ch, LC_C_LOCALE));
      ASSERT_EQ(islower(ch), islower_l(ch, LC_C_LOCALE));
      ASSERT_EQ(isprint(ch), isprint_l(ch, LC_C_LOCALE));
      ASSERT_EQ(ispunct(ch), ispunct_l(ch, LC_C_LOCALE));
      ASSERT_EQ(isspace(ch), isspace_l(ch, LC_C_LOCALE));
      ASSERT_EQ(isupper(ch), isupper_l(ch, LC_C_LOCALE));
      ASSERT_EQ(isxdigit(ch), isxdigit_l(ch, LC_C_LOCALE));
      ASSERT_EQ(tolower(ch), tolower_l(ch, LC_C_LOCALE));
      ASSERT_EQ(toupper(ch), toupper_l(ch, LC_C_LOCALE));
    });
  }
}

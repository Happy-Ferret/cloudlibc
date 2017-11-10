// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// SPDX-License-Identifier: BSD-2-Clause

#include <stdatomic.h>
#include <testing.h>

TEST(atomic_flag, example) {
  atomic_flag flag = ATOMIC_FLAG_INIT;

  // Test non-explicit functions.
  ASSERT_FALSE(atomic_flag_test_and_set(&flag));
  ASSERT_TRUE(atomic_flag_test_and_set(&flag));
  ASSERT_TRUE(atomic_flag_test_and_set(&flag));
  atomic_flag_clear(&flag);

  // Test explicit functions.
  ASSERT_FALSE(atomic_flag_test_and_set_explicit(&flag, memory_order_relaxed));
  ASSERT_TRUE(atomic_flag_test_and_set_explicit(&flag, memory_order_relaxed));
  ASSERT_TRUE(atomic_flag_test_and_set_explicit(&flag, memory_order_relaxed));
  atomic_flag_clear_explicit(&flag, memory_order_relaxed);

  ASSERT_FALSE(atomic_flag_test_and_set_explicit(&flag, memory_order_relaxed));
}

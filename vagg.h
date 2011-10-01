#ifndef VAGG_H
#define VAGG_H
#include <stdlib.h>
#include "vagg_macros.h"

enum vagg_show {
  vagg_display_success,
  vagg_hide_sucess
};

/**
 * Compile to noop if TEST is not #DEFINED
 */
#ifdef VAGG_TEST
/**
 * @brief Starts a test suite.
 *
 * @param show_all If 0, show success as well as failure, else, show only failures
 */
void vagg_start(enum vagg_show show_all);
/**
 * @brief A predicate test.
 *
 * @param predicate A predicate that has to be true for the test to pass.
 * @param msg A message to display in case of failure.
 */
void vagg_ok(int predicate, char* msg);
/**
 * @brief Test if a number is in a range.
 *
 * @param value The value to test.
 * @param ref The reference value to test against.
 * @param threshold The treshold which is acceptable
 * @param msg A message to display in case of failure.
 */
void vagg_range(double value, double ref, double threshold, char* msg);
/**
 * @brief Test buffer equality
 *
 * @param buf1 The first buffer to compare.
 * @param buf1_len The length of the first buffer.
 * @param buf2 The second buffer to compare.
 * @param buf2_len The length of the first buffer.
 * @param msg A message to display in case of failure.
 */
void vagg_bufeq(const void* buf1, size_t buf1_len, const void* buf2, size_t buf2_len, char* msg);
/**
 * @brief Ends the test suite and display the results.
 */
void vagg_end();
#else
#define vagg_start(...)
#define vagg_bufeq(...)
#define vagg_range(...)
#define vagg_ok(...)
#define vagg_end()
#endif

#endif /* VAGG_H */

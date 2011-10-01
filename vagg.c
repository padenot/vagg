#include <stdio.h>
#include <math.h>
#include <strings.h>
#include "vagg.h"
#include "vagg_macros.h"

#ifdef VAGG_TEST
static unsigned success_count = 0;
static unsigned test_index = 0;
static unsigned show_success = 0;

static void failed(char* msg) {
    VAGG_LOG(VAGG_LOG_CRITICAL, "\ttest %d failed : %s", test_index, msg);
}

static void success(char* msg) {
    VAGG_LOG(VAGG_LOG_OK, "\ttest %d succeeded : %s", test_index, msg);
}

void vagg_start(enum vagg_show show_all) {
  show_success = show_all;
  success_count = 0;
  test_index = 0;
  VAGG_LOG(VAGG_LOG_DEBUG, "starting test suite.");
}

void vagg_ok(int predicate, char* msg) {
  test_index++;
  if(!predicate) {
    success_count++;
    if (show_success) {
      success(msg);
    }
  } else {
    failed(msg);
  }
}

void vagg_range(double value, double ref, double threshold, char* msg) {
  test_index++;
  if (fabs(value - ref) <= threshold) {
    success_count++;
    if (show_success) {
      success(msg);
    }
  } else {
    failed(msg);
  }
}

void vagg_bufeq(const void* buf1, size_t buf1_len, const void* buf2, size_t buf2_len, char* msg) {
  test_index++;
  if(buf1_len != buf2_len) {
    failed(msg);
  }
  if (bcmp(buf1, buf2, buf1_len)) {
    failed(msg);
  } else {
    if (show_success) {
      success(msg);
    }
    success_count++;
  }
}

void vagg_end() {
  if (success_count == test_index) {
    VAGG_LOG(VAGG_LOG_OK, "test suite ended : %u/%u passed. success.", success_count, test_index);
  } else {
    VAGG_LOG(VAGG_LOG_CRITICAL, "test suite ended : %u/%u passed. failed.", success_count, test_index);
  }
}
#endif // VAGG_TEST

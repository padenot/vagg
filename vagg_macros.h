#ifndef MACROS_H
#define MACROS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <errno.h>
#include <string.h>

#define VAGG_MACRO_BEG do {
#define VAGG_MACRO_END } while(0);

#define VAGG_SYSCALL(x)                                               \
  VAGG_MACRO_BEG                                                      \
  if(x == -1) {                                                       \
  	VAGG_LOG(VAGG_LOG_FATAL, "#! SYSCALL FAILED : %s:%d:%s:%s",       \
        __FILE__, __LINE__, #x, strerror(errno));                     \
    abort();                                                          \
  }                                                                   \
  VAGG_MACRO_END

#ifdef VAGG_DEBUG
  enum vagg_log_level {
    VAGG_LOG_FATAL,    // this error will kill the program
    VAGG_LOG_CRITICAL, // nasty error
    VAGG_LOG_WARNING,  // something is getting wrong
    VAGG_LOG_OK,       // working
    VAGG_LOG_DEBUG,    // normal output message
    VAGG_COLOR_RESET,  // resets the color to user default
    VAGG_COLORS_SIZE
  };

	#ifndef VAGG_LOG_LEVEL
    #define VAGG_LOG_LEVEL VAGG_LOG_DEBUG
	#endif

	/* The current indent level */
  static size_t vagg_log_indent_level = 0;
  /* Indents the log by one level */
  #define VAGG_LOG_INDENT vagg_log_indent_level++;
  /* Unindents the log by one level */
  #define VAGG_LOG_UNINDENT VAGG_ASSERT(vagg_log_indent_level-- > (size_t)0, "Log indent level is now negative");
  static const char* VAGG_COLORS[VAGG_COLORS_SIZE] = {
    "\e[1;91m", // FATAL bold red.
    "\e[0;91m", // CRITICAL red.
    "\e[0;93m", // WARNING yellow.
    "\e[0;92m", // OK green.
    "",         // DEBUG normal.
    "\e[0m"     // reset.
  };

  /* Logs to stdout, using colors for the levels */
  #define VAGG_LOG(level, ...)                                 \
    VAGG_MACRO_BEG                                             \
      if(level <= VAGG_LOG_LEVEL) {                            \
        size_t i;                                              \
        fprintf(stdout, "%s", VAGG_COLORS[level]);             \
        for(i=0; i < vagg_log_indent_level ; i++) {            \
          fprintf(stdout, "\t");                               \
        }                                                      \
        if (pthread_self() != 0) {                             \
          fprintf(stdout, "[%ld] ", pthread_self());           \
        }                                                      \
        fprintf(stdout, __VA_ARGS__);                          \
        fprintf(stdout, "\n");                                 \
        fprintf(stdout, "%s", VAGG_COLORS[VAGG_COLOR_RESET]);  \
      }                                                        \
    VAGG_MACRO_END

  /* If ASSERT_FATAL is defined, a failing asserts will kill the program. */
  #ifdef VAGG_ASSERT_FATAL
    #define VAGG_ASSERT(test, msg)                        \
      if (!test) {                                        \
        VAGG_LOG(VAGG_LOG_CRITICAL, "#! ASSERT FAILED %s:%d:%s\n",  \
            __FILE__, __LINE__, #msg);                    \
        abort();                                          \
      }
  #else
    #define VAGG_ASSERT(test, msg)                        \
      if (!test) {                                        \
        VAGG_LOG(VAGG_LOG_CRITICAL, "#! ASSERT FAILED %s:%d:%s\n",  \
            __FILE__, __LINE__, #msg);                    \
      }
  #endif

  /**
   * @brief Assert that a value is in a range. Strict comparison version.
   *
   * @param x The value to check.
   * @param ref The reference value.
   * @param thres The threshold.
   */
  #define VAGG_BOUND(x, ref, thres)                                            \
    if (fabs(x - ref < thres)) {                                               \
      VAGG_LOG(VAGG_LOG_CRITICAL, "#! ASSERT FAILED %s:%d, %d should be > %d and < %d ", \
          __FILE__, __LINE__, x, ref-thres, ref+thres);                        \
    }

  /**
   * @brief Assert that a value is in a range. Inclusive comparison version.
   *
   * @param x The value to check.
   * @param ref The reference value.
   * @param thres The threshold.
   */
  #define VAGG_BOUNDI(x, ref, thres)                                                \
    if (fabs(x - ref) <= thres) {                                                   \
      VAGG_LOG(VAGG_LOG_CRITICAL, "#! ASSERT FAILED %s:%d, %d should be >= %d and <= %d ",    \
          __FILE__, __LINE__, x, ref-thres, ref+thres);                             \
    }

  /**
   * @brief Assert that a value is zero.
   *
   * @param x The value to check.
   */
  #define VAGG_ZERO(x)                                                \
    if (x != 0) {                                                      \
      VAGG_LOG(VAGG_LOG_CRITICAL, "#! ASSERT FAILED %s:%d, %d should be 0",   \
          __FILE__, __LINE__, x);                                     \
    }

  /**
   * @brief Assert that a value is positive. Strict comparison version.
   *
   * @param x The value to check.
   */
  #define VAGG_POS(x)                                                 \
    if (x < 0) {                                                      \
      VAGG_LOG(VAGG_LOG_CRITICAL, "#! ASSERT FAILED %s:%d, %d should be > 0",   \
          __FILE__, __LINE__, x);                                     \
    }
  /**
   * @brief Assert that a value is negative. Strict comparison version
   *
   * @param x The value to check.
   */
  #define VAGG_NEG(x)                                                 \
    if (x > 0) {                                                      \
      VAGG_LOG(VAGG_LOG_CRITICAL, "#! ASSERT FAILED %s:%d, %d should be < 0.",  \
          __FILE__, __LINE__, x);                                     \
    }

  /**
   * @brief Assert that a value is positive. Inclusive comparison version.
   *
   * @param x The value to check.
   */
  #define VAGG_POSI(x)                                                \
    if (x <= 0) {                                                     \
      VAGG_LOG(VAGG_LOG_CRITICAL, "#! ASSERT FAILED %s:%d, %d should be >= 0",  \
          __FILE__, __LINE__, x);                                     \
    }

  /**
   * @brief Assert that a value is negative. Inclusive comparison version
   *
   * @param x The value to check.
   */
  #define VAGG_NEGI(x)                                                \
    if (x >= 0) {                                                     \
      VAGG_LOG(VAGG_LOG_CRITICAL, "#! ASSERT FAILED %s:%d, %d should be <= 0.", \
          __FILE__, __LINE__, x);                                     \
    }
#else
    #define VAGG_ASSERT(...);
    #define VAGG_LOG(...);
    #define VAGG_BOUND(...);
    #define VAGG_BOUNDI(...);
		#define VAGG_ZERO(...);
    #define VAGG_POS(...);
    #define VAGG_NEG(...);
    #define VAGG_POSI(...);
    #define VAGG_NEGI(...);
#endif // VAGG_DEBUG

// UNUSED(arg) to remove compiler warning for a parameter
// void func() UNUSED to remove compiler warning for a function
#ifdef VAGG_UNUSED
#elif defined(__GNUC__)
# define VAGG_UNUSED(x) UNUSED_ ## x __attribute__((unused))
# define VAGG_FUNUSED __attribute__((unused))
#elif defined(__LCLINT__)
# define VAGG_UNUSED(x) /*@unused@*/ x
#else
# define VAGG_UNUSED(x) x
#endif

/**
 * Traces the allocations and the deallocations.
 * if VAGG_PRINT_ALLOC is defined, a message is logged every time an allocation
 * occurs.
 * at a normal exit of the program, the balance of alloc and dealloc is
 * outputed.
 */
#ifdef VAGG_COUNT_ALLOC
	static size_t vagg_alloc_count = 0;

	static void trace_exit_handler() VAGG_FUNUSED;
	static void trace_exit_handler()
	{
    if (vagg_alloc_count) {
      VAGG_LOG(VAGG_LOG_CRITICAL, "Alloc balance: %zu. Memory leaks detected.", vagg_alloc_count);
    } else {
      VAGG_LOG(VAGG_LOG_OK, "Alloc balance: %zu. No memory leaks.", vagg_alloc_count);
    }
		exit(0);
	}

  static size_t vagg_alloc_balance() VAGG_FUNUSED;
  static size_t vagg_alloc_balance()
  {
    return vagg_alloc_count;
  }

  #define vagg_set_exit_handler()                            \
    if(atexit(trace_exit_handler)) {                    \
      VAGG_LOG(VAGG_LOG_FATAL, "couldnt set exit function.\n");   \
      abort();                                          \
    }
  #ifdef VAGG_PRINT_ALLOC
    #define VAGG_ALLOC(x)                           \
    VAGG_ALLOC_IMPL(x);                             \
    VAGG_LOG(VAGG_LOG_DEBUG, "Alloc in %s.", __func__);  \
    vagg_alloc_count++;
  #else
    #define VAGG_ALLOC(x)                           \
    VAGG_ALLOC_IMPL(x);                             \
    vagg_alloc_count++;
  #endif

  #ifdef VAGG_PRINT_ALLOC
    #define VAGG_DELETE(x)                              \
      VAGG_DELETE_IMPL(x);                              \
      VAGG_LOG(VAGG_LOG_DEBUG, "Delete in %s.", __func__);   \
      vagg_alloc_count--;
  #else
    #define VAGG_DELETE(x)                              \
      VAGG_DELETE_IMPL(x);                              \
      vagg_alloc_count--;
  #endif
#else
  #define VAGG_ALLOC(x) VAGG_ALLOC_IMPL(x)
  #define VAGG_DELETE(x) VAGG_DELETE_IMPL(x)
	#define vagg_set_exit_handler()
#endif

#define VAGG_ALLOC_IMPL(x)     \
	malloc(x);							\

#define VAGG_DELETE_IMPL(x) \
  free(x);						 \

#endif /* MACROS_H */

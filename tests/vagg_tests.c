#include "vagg.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* This won't make the compiler issue a warning */
void unused(); VAGG_FUNUSED
void unused(int VAGG_UNUSED(i)) {
	printf("this is unused.\n");
}

int main() {
  /* test logging */
  VAGG_LOG(VAGG_LOG_FATAL   , ("LOG_FATAL   "));
  VAGG_LOG(VAGG_LOG_CRITICAL, ("LOG_CRITICAL"));
  VAGG_LOG(VAGG_LOG_WARNING , ("LOG_WARNING "));
  VAGG_LOG(VAGG_LOG_OK      , ("LOG_OK      "));
  VAGG_LOG(VAGG_LOG_DEBUG   , ("LOG_DEBUG   "));

  /* test testing. */
  vagg_start(vagg_hide_sucess);
  vagg_ok(1, "should succeed");
  vagg_ok(0, "should fail");
  vagg_range(3.1, 3.0, 0.2, "should succeed");
  vagg_range(3.1, 3.0, 0.01, "should fail");
  vagg_range(3.1, 3.0, 0.0, "should fail");
  float a1[3] = {0.0, 0.0, 0.0};
  a1[1]++;
  float a2[3] = {0.1, 0.0, 0.0};
  a2[1]++;
  vagg_bufeq(a1, 3, a1, 3, "should succeed.");
  vagg_bufeq(a1, 3, a2, 3, "should fail.");
  vagg_end();
  vagg_start(vagg_display_success);
  vagg_ok(1, "should succeed.");
  vagg_end();
  VAGG_POS(-1); /* failure */
  VAGG_POS(1); /* success */
  VAGG_NEG(1); /* failure */
  VAGG_NEG(-1); /* success */
  VAGG_POS(0); /* failure */
  VAGG_NEG(0); /* failure */
  VAGG_POSI(-1); /* failure */
  VAGG_POSI(1); /* success */
  VAGG_NEGI(1); /* failure */
  VAGG_NEGI(-1); /* success */
  VAGG_NEGI(0); /* success */
  VAGG_POSI(0); /* success */
  VAGG_BOUND(1, 0, 2); /* success */
  VAGG_BOUND(3, 0, 2); /* failure */
	VAGG_ZERO(0); /* success */
	VAGG_ZERO(1); /* failure */
	vagg_end();

  /* test alloc counting */
	vagg_set_exit_handler();
  int* int_array = VAGG_ALLOC(10*sizeof(int));
  int* int_array2 = VAGG_ALLOC(10*sizeof(int));
  int* int_array3 = VAGG_ALLOC(10*sizeof(int));
	int_array[0]++;
	int_array3[0]++;

  VAGG_DELETE(int_array2);
  VAGG_LOG(VAGG_LOG_WARNING, "Memory chunk not deallocated : %zu", vagg_alloc_balance());

  /* syscalls checking */
  int fd;
  VAGG_SYSCALL((fd = open("vagg_tests.c", O_RDONLY))); /* success */
  VAGG_SYSCALL(close(fd)); /* success */
  VAGG_SYSCALL(close(-1)); /* failure */


  return 0;
}

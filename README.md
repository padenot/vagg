# Vägg, some defensive-coding helpers in C

This project includes a tiny unit test function set, which is quite enough for
my need, and a set of macro to make defensive coding more enjoyable and
systematic. And it has pretty color output, too.

## Examples

``` c
/* Allow to disable warnings specific warnings, to encourage warning
 * reduction. */
// This won't make the compiler issue a warning
void unused(int i); VAGG_FUNUSED
void unused(int VAGG_UNUSED(i)) {
	printf("this is unused.\n");
}

/* logging */
VAGG_LOG(VAGG_LOG_FATAL   , ("LOG_FATAL   "));
VAGG_LOG(VAGG_LOG_CRITICAL, ("LOG_CRITICAL"));
VAGG_LOG(VAGG_LOG_WARNING , ("LOG_WARNING "));
VAGG_LOG(VAGG_LOG_OK      , ("LOG_OK      "));
VAGG_LOG(VAGG_LOG_DEBUG   , ("LOG_DEBUG   "));

/* unit testing */
vagg_start(vagg_hide_sucess);
vagg_ok(0, "should succeed");
vagg_ok(1, "should fail");
vagg_range(3.1, 3.0, 0.2, "should succeed");
vagg_range(3.1, 3.0, 0.01, "should fail");
vagg_range(3.1, 3.0, 0.0, "should fail");
vagg_end();
vagg_start(vagg_display_success);
float a1[3] = {0.0, 0.0, 0.0};
a1[1]++;
float a2[3] = {0.1, 0.0, 0.0};
a2[1]++;
vagg_bufeq(a1, 3, a1, 3, "should succeed.");
vagg_bufeq(a1, 3, a2, 3, "should fail.");
vagg_end();

/* asserts */
VAGG_POS(-1); // fail
VAGG_NEG(1); // fail
VAGG_POSI(0); // succeed
VAGG_NEGI(1); // fail
VAGG_BOUND(3, 0, 2); // fail
VAGG_ZERO(0); // succeed
VAGG_ASSERT(1 == 2, "This should fail");

/* Light memory leak detection */
/* This has to be called once to setup the handler called at the end of the
 * program */
vagg_set_exit_handler();
int* int_array = VAGG_ALLOC(10*sizeof(int));
int* int_array2 = VAGG_ALLOC(10*sizeof(int));

int_array[4] = 6;

/* A deallocation is missing */
VAGG_DELETE(int_array2);
```

## Compile time switches
- `VAGG_DEBUG`: turns on logging & assertions;
- `VAGG_TEST`: turns on testing;
- `VAGG_ASSERT_FATAL`: make assert kill the program;
- `VAGG_COUNT_ALLOC`: enable alloc counting;
- `VAGG_PRINT_ALLOC`: enable alloc logging.

## Usage
Assuming we use git, and we are inside our project directory :
``` sh
	git submodule add git://github.com/padenot/vagg.git

	cd vagg && make # builds static library, dynamic library and .o file.
```
If you want to update to the latest revision, once again inside the root project
directory :
``` sh
	git submodule update
```

## License
Vägg is published under the terms of the new BSD License : http://www.freebsd.org/copyright/license.html

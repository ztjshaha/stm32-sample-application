#include <stdarg.h>
#include <stddef.h>
#include <limits.h>
#include <setjmp.h>
#include <cmocka.h>

#include "module.h"

//#include "module.c"

typedef struct {int input; int expected;} vector_t;

const vector_t vectors[] = {
  {0,0},
  {1,2},
  {2,4},
  {INT_MAX/2, INT_MAX-1},
  {INT_MAX, -2},
};

static void test_external(void **state)
{
    int actual;
    int i;

    for (i = 0; i < sizeof(vectors)/sizeof(vector_t); i++)
    {
      const vector_t *vector = &vectors[i];
      actual = external(vector->input);
      assert_int_equal(vector->expected, actual);
    }
}

int main()
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_external),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef int (*test_func)();

typedef struct
{
    char name[50];
    test_func function;
} test_data;

#define test_printf             \
    (printf("%s: ", __func__)); \
    printf

#define test_assert(expr, str)                                                                        \
    {                                                                                                 \
        if (!(expr))                                                                                  \
        {                                                                                             \
            printf("%s: \033[1;31m [FAIL] \033[0m %s in %s:%d\n", __func__, str, __FILE__, __LINE__); \
            return -1;                                                                                \
        }                                                                                             \
    }

#define TEST(f)                   \
    {                             \
        .name = #f, .function = f \
    }

#define test_list test_data all_tests[]

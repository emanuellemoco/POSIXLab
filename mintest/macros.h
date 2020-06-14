#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

typedef void *(*test_func)(void *args);

typedef struct
{
    char name[50];
    test_func function;
    int res;
} test_data;

#define test_printf             \
    (printf("%s: ", __func__)); \
    printf

#define test_assert(expr, str)                                                     \
    {                                                                              \
        if (!(expr))                                                               \
        {                                                                          \
            printf("%s: [FAIL] %s in %s:%d\n", __func__, str, __FILE__, __LINE__); \
            *res = -1;                                                             \
        }                                                                          \
    }

#define TEST(f)                   \
    {                             \
        .name = #f, .function = f \
    }

#define test_list test_data all_tests[]

#include "mintest/macros.h"

//cause erro e termine com falha de segmentação
void *test1(void *_arg)
{
    int *res = (int *)_arg;
    test_printf("Entrou\n");
    *res = 1;
    raise(SIGSEGV);
    return NULL;
}

//cause erro e termine com divisão por zero
void *test2(void *_arg)
{
    int *res = (int *)_arg;
    test_printf("Entrou\n");
    test_assert(1 / 0, "This always fails!");
    *res = 2;
    return NULL;
}

//fique em loop infinito
void *test3(void *_arg)
{
    int i;
    int *res = (int *)_arg;
    while (1)
    {
        //test_printf("Entrou\n");
    }

    *res = 3;
    return NULL;
}

//faça muito trabalho, mas eventualmente acabe (sem usar sleep )
void *test4(void *_arg)
{
    int i;
    int *res = (int *)_arg;
    test_printf("Entrou\n");
    for (i = 0; i < 1000000000; i++)
    {
        i++;
    }
    *res = 4;
    return NULL;
}

//tenha asserts que falham e passem no mesmo teste
void *test5(void *_arg)
{
    int *res = (int *)_arg;
    test_printf("Entrou\n");
    *res = 5;
    test_assert(1 == 0, "This always fails!");
    test_assert(1 == 1, "This always succeeds");
    return NULL;
}

//tenha testes que façam muitos prints
void *test6(void *_arg)
{
    int i;
    int *res = (int *)_arg;
    test_printf("Entrou\n");
    for (i = 0; i < 1000000; i++)
    {
        test_printf("oi\n");
    }
    *res = 6;
    return NULL;
}

//tenha testes que sejam rápidos e testes que sejam lentos (pode usar sleep para simular).
void *test7(void *_arg)
{
    int *res = (int *)_arg;
    test_printf("Entrou\n");
    *res = 7;
    sleep(60);
    return NULL;
}

test_list = {TEST(test1), TEST(test2), TEST(test3), TEST(test4), TEST(test5), TEST(test6), TEST(test7)};

#include "mintest/runner.h"
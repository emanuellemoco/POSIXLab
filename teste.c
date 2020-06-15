#include "mintest/macros.h"

//cause erro e termine com falha de segmentação
int test1()
{
    test_printf("Entrou\n");
    raise(SIGSEGV);
    return 0;
}

//cause erro e termine com divisão por zero
int test2()
{
    test_printf("Entrou\n");
    test_assert(1 / 0, "This always fails!");
    return 0;
}

//fique em loop infinito
int test3()
{
    int i;
    while (1)
    {
        //test_printf("Entrou\n");
    }
    return 0;
}

//faça muito trabalho, mas eventualmente acabe (sem usar sleep )
int test4()
{
    int i;
    test_printf("Entrou\n");
    for (i = 0; i < 1000000000; i++)
    {
        i++;
    }
    return 0;
}

//tenha asserts que falham e passem no mesmo teste
int test5()
{
    test_printf("Entrou\n");
    test_assert(1 == 0, "This always fails!");
    test_assert(1 == 1, "This always succeeds");
    return 0;
}

//tenha testes que façam muitos prints
int test6()
{
    int i;
    test_printf("Entrou\n");
    for (i = 0; i < 1000000; i++)
    {
        test_printf("oi\n");
    }
    return 0;
}

//tenha testes que sejam rápidos e testes que sejam lentos (pode usar sleep para simular).
int test7()
{
    test_printf("Entrou\n");
    sleep(60);
    return 0;
}

test_list = {TEST(test1), TEST(test2), TEST(test3), TEST(test4), TEST(test5), TEST(test6), TEST(test7)};

#include "mintest/runner.h"
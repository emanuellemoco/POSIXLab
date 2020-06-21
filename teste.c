#include "mintest/macros.h"

//cause erro e termine com falha de segmentação
int test1()
{
    alarm(2);
    // test_printf("Entrou\n");
    raise(SIGSEGV);

    return 0;
}

//cause erro e termine com divisão por zero
int test2()
{
    alarm(2);
    // test_printf("Entrou\n");
    //int i = 1 / 0;
    test_assert(1 / 0 == 0, "This always fails!");

    return 0;
}

//fique em loop infinito
int test3()
{
    alarm(2);
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
    alarm(2);
    int i;
    // test_printf("Entrou\n");
    for (i = 0; i < 1000000000; i++)
    {
        i++;
    }

    return 0;
}

//tenha asserts que falham e passem no mesmo teste
int test5()
{
    alarm(2);
    // test_printf("Entrou\n");
    test_assert(1 == 1, "This always succeeds");
    test_assert(1 == 0, "This always fails!");

    return 0;
}

//tenha testes que façam muitos prints
int test6()
{
    alarm(2);
    int i;
    for (i = 0; i < 100000; i++)
    {
        ///test_printf("oi");
    }

    return 0;
}

//tenha testes que sejam rápidos e testes que sejam lentos (pode usar sleep para simular).
int test7()
{
    alarm(2);
    sleep(10);

    return 0;
}

test_list = {TEST(test1), TEST(test2), TEST(test3), TEST(test4), TEST(test5), TEST(test6), TEST(test7)};

#include "mintest/runner.h"
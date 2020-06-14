
void sig_sf(int num)
{ //segmentation fault
    printf("entrou na sig_sf\n");
}

void sig_fp(int num)
{ //float point ex
    printf("entrou na sig_fp\n");
}

void sig_cc(int num)
{ //ctrl c
    printf("entrou na sig_cc\n");
    printf("Tem certeza? [s/n] ");
    char v;
    scanf("%c", &v);
    printf("%c", v);

    if (v == 's')
        //     Se o usuário digitar s o programa parará todos os testes em execução. Cada teste parado fica com status
        // [STOP] e é mostrado o resumo de quantos testes passaram e quantos não passaram.
        exit(0);
}

int main(int argc, char *argv[])
{
    printf("%s", argv[1]);
    printf("%s", argv[2]);
    printf("%d", argc);
    int size = sizeof(all_tests) / sizeof(test_data);
    printf("Running %d tests:\n", size);
    printf("=====================\n\n");
    int pass_count = 0;
    pthread_t *tids = malloc(sizeof(pthread_t) * size);

    struct sigaction s_sf;
    s_sf.sa_handler = sig_sf; // aqui vai a função a ser executada
    sigemptyset(&s_sf.sa_mask);
    s_sf.sa_flags = 0;
    sigaction(SIGSEGV, &s_sf, NULL);

    struct sigaction s_fp;
    s_fp.sa_handler = sig_fp; // aqui vai a função a ser executada
    sigemptyset(&s_fp.sa_mask);
    s_fp.sa_flags = 0;
    sigaction(SIGFPE, &s_fp, NULL);

    struct sigaction s_cc;
    s_cc.sa_handler = sig_cc; // aqui vai a função a ser executada
    sigemptyset(&s_cc.sa_mask);
    s_cc.sa_flags = 0;
    sigaction(SIGINT, &s_cc, NULL);

    if (argc > 1)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 1; j < argc; j++)
            {
                // printf("%s : %s\n  ", argv[j], all_tests[i].name);
                if (strcmp(argv[j], all_tests[i].name) == 0)
                {
                    // printf("entrei aqui\n");
                    pthread_create(&tids[i], NULL, all_tests[i].function, &all_tests[i].res);
                }
            }
        }

        for (int i = 0; i < size; i++)
        {
            for (int j = 1; j < argc; j++)
            {
                if (strcmp(argv[j], all_tests[i].name) == 0)
                {
                    pthread_join(tids[i], NULL);
                }
            }
        }
    }
    else
    {

        for (int i = 0; i < size; i++)
        {
            pthread_create(&tids[i], NULL, all_tests[i].function, &all_tests[i].res);
            // if (all_tests[i].function() >= 0)
            // {
            //     printf("%s: [PASS]\n", all_tests[i].name);
            //     pass_count++;
            // };
        }

        for (int i = 0; i < size; i++)
        {
            pthread_join(tids[i], NULL);
            printf("Res: %d \n", all_tests[i].res);

            //valor do return: all_tests[i].res
        }
    }

    printf("\n\n=====================\n");
    printf("%d/%d tests passed\n", pass_count, size);
    return 0;
}

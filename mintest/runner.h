
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
    s_sf.sa_handler = sig_sf;
    sigemptyset(&s_sf.sa_mask);
    s_sf.sa_flags = 0;
    sigaction(SIGSEGV, &s_sf, NULL);

    struct sigaction s_fp;
    s_fp.sa_handler = sig_fp;
    sigemptyset(&s_fp.sa_mask);
    s_fp.sa_flags = 0;
    sigaction(SIGFPE, &s_fp, NULL);

    struct sigaction s_cc;
    s_cc.sa_handler = sig_cc;
    sigemptyset(&s_cc.sa_mask);
    s_cc.sa_flags = 0;
    sigaction(SIGINT, &s_cc, NULL);

    pid_t f;
    printf("Pai: %d, id %d\n", getpid(), 0);

    int st;

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
                    //pthread_create(&tids[i], NULL, all_tests[i].function, &all_tests[i].res);
                    f = fork();
                    if (f == 0)
                    {
                        printf("Filho %d Pai: %d id %d\n", getpid(), getppid(), i);
                        return all_tests[i].function();
                    }
                }
            }
        }

        for (int j = 1; j < argc; j++)
        {
            wait(&st);
            if (WIFEXITED(st))
            {
                if ((WEXITSTATUS(st) == 0))
                    pass_count++;
            }
        }
    }
    else
    {

        for (int i = 0; i < size; i++)
        {
            //pthread_create(&tids[i], NULL, all_tests[i].function, &all_tests[i].res);
            f = fork();
            if (f == 0)
            {
                printf("Filho %d Pai: %d id %d\n", getpid(), getppid(), i);
                return all_tests[i].function();
            }
        }

        for (int i = 0; i < size; i++)
        {
            //pid_t f2 = wait(&i);
            //printf("id do primeiro filho a acabar: %d, pid %d\n", WEXITSTATUS(i), f2);
            wait(&st);
            if (WIFEXITED(st))
            {
                if ((WEXITSTATUS(st) == 0))
                    pass_count++;
            }
        }
    }

    printf("\n\n=====================\n");
    printf("%d/%d tests passed\n", pass_count, size);
    return 0;
}

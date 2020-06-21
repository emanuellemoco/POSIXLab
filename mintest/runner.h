
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
    printf("Você deseja mesmo sair [s/n]?");
    char v;
    scanf("%c", &v);
    if (v == 's')
        exit(0);
}

int main(int argc, char *argv[])
{
    int size = sizeof(all_tests) / sizeof(test_data);
    // printf("Running %d tests:\n", size);
    // printf("=====================\n\n");
    int pass_count = 0;
    pthread_t *tids = malloc(sizeof(pthread_t) * size);

    struct sigaction s_cc;
    s_cc.sa_handler = sig_cc;
    sigemptyset(&s_cc.sa_mask);
    s_cc.sa_flags = 0;
    sigaction(SIGINT, &s_cc, NULL);

    pid_t f;
    int st, pid;
    int qtd = 0;
    int lista_pid[7];

    if (argc > 1)
    {
        printf("Running %d tests:\n", argc - 1);
        printf("=====================\n\n");
        for (int i = 0; i < size; i++)
        {
            for (int j = 1; j < argc; j++)
            {
                if (strcmp(argv[j], all_tests[i].name) == 0)
                {
                    qtd++;
                    lista_pid[j - 1] = fork();
                    if (lista_pid[j - 1] == 0)
                    {
                        return all_tests[i].function();
                    }
                }
            }
        }
    }
    else
    {
        printf("Running %d tests:\n", size);
        printf("=====================\n\n");

        for (int i = 0; i < size; i++)
        {
            //pthread_create(&tids[i], NULL, all_tests[i].function, &all_tests[i].res);
            qtd++;
            lista_pid[i] = fork();
            if (lista_pid[i] == 0)
            {
                return all_tests[i].function();
            }
        }
    }

    for (int j = 0; j < qtd; j++)
    {

        pid = waitpid(lista_pid[j], &st, 0);

        if (WIFEXITED(st))
        {
            if ((WEXITSTATUS(st) == 0))
            {
                pass_count++;

                printf("%s: \033[1;32m [PASS] \033[0m \n", all_tests[j].name);
            }
        }

        if (WIFSIGNALED(st))
        {
            printf("%s: \033[1;31m [FAIL] \033[0m %s\n", all_tests[j].name, strsignal(WTERMSIG(st)));
        }
    }

    printf("\n\n=====================\n");
    printf("%d/%d tests passed\n", pass_count, size);
    return 0;
}

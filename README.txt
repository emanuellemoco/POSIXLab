POSIX Lab - Emanuelle Moço

Implementação 

Dentro do main existe duas partes principais pois o código está divido entre rodar automaticamente todos os testes, ou rodar os testes que o usuário deu input. 

Ao fazer os forks, os pids são salvos em um vetor -> lista_pid.

No último for é utilizado waitpid, que espera um processo específico acabar, assim, é possível obter os sinais obtido pelo teste. 
Quando o sinal é 0 (WEXITSTATUS), o teste passou. 
O uso do WIFSIGNALED permite saber o sinal dos erros emitidos.

Os prints estão com cores específicas:
[PASS] -> verde
[FAIL] -> vermelho

Também é utilizado sinais, por meio do SIGINT, para fazer a saída quando o usuário aperta ctrl+c e digita 's'.


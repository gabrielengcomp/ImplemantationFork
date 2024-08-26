
# Problema Produtor/Consumidor

## Descrição Geral

Este projeto implementa a solução clássica do problema Produtor/Consumidor usando processos e compartilhamento de memória através de arquivos.

## Funcionamento

Dois processos compartilham uma mesma área de memória, representada por um arquivo denominado `buffer.txt`. Esses processos funcionam da seguinte maneira:

- **Produtor:** Escreve um valor aleatório `r ∈ [0, 99]` no final do arquivo `buffer.txt`. Após a inserção, o produtor espera por `s` segundos, onde `s` é um valor aleatório `s ∈ [1, 3]`, antes de inserir o próximo valor.
  
- **Consumidor:** Remove valores do início do arquivo `buffer.txt`, imprimindo-os na tela. Assim como o produtor, o consumidor também espera por `s` segundos antes de remover o próximo valor.

## Sincronização

Para evitar problemas de concorrência ao acessar o arquivo `buffer.txt`, os processos utilizam um mecanismo de "lock" (trava):

- Antes de escrever ou ler o arquivo `buffer.txt`, o processo cria um arquivo `buffer.txt.lock`, indicando que o `buffer.txt` está em uso.
- Após a conclusão da escrita ou leitura, o processo apaga o arquivo `buffer.txt.lock`.
- Se um processo tentar acessar o `buffer.txt` enquanto o arquivo `buffer.txt.lock` existir, ele deve esperar até que o arquivo de trava seja removido, indicando que o `buffer.txt` está disponível.

## Inicialização do Arquivo

O arquivo `buffer.txt` é inicializado com 10 inteiros (um por linha) antes do início da execução dos processos.

## Execução

Para executar o programa, utilize o comando:

```bash
$ ./produtor-consumidor
```

Exemplo de saída:

```
[Consumidor] 91
[Consumidor] 10
[Produtor] 62
[Consumidor] 33
[Consumidor] 79
[Produtor] 9
[Produtor] 52
```

## Tecnologias Utilizadas

- Linguagem de programação: C/C++
- Manipulação de arquivos
- Controle de processos usando `fork()`
- Sincronização básica com arquivos de trava

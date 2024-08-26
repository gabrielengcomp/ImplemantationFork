#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //sleep e unsleep
#include <time.h> //rand    

//Gabriel Santos e Vicente Zanatta

void inic_buffer() {
    FILE *fp = fopen("buffer.txt", "w");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }
    //preenche o arquivo buffer
    for (int i = 0; i < 10; i++) {
        fprintf(fp, "%d\n", rand() % 100);
    }

    fclose(fp);
}

void tranca_arquivo() {
    while (fopen("buffer.txt.lock", "r") != NULL) {
        usleep(100000); //espera 100 ms antes de tentar novamente
    }
    FILE *fp = fopen("buffer.txt.lock", "w");
    if (fp == NULL) {
        perror("Erro ao criar o arquivo lock");
        exit(1);
    }
    fclose(fp);
}

void destranca_arquivo() {
    remove("buffer.txt.lock");
}

void produtor() {
    srand(time(NULL) ^ (getpid() << 16));//semente aleatória para evitar repetição
    while (1) {
        int r = rand() % 100;
        int s = rand() % 3 + 1;

        tranca_arquivo();

        FILE *fp = fopen("buffer.txt", "a");
        if (fp == NULL) {
            perror("Erro ao abrir o arquivo ");
            destranca_arquivo();
            exit(1);
        }

        fprintf(fp, "%d\n", r);
        printf("[Produtor] %d\n", r);
        fclose(fp);

        destranca_arquivo();

        sleep(s);
    }
}

void consumidor() {
    srand(time(NULL) ^ (getpid() << 16));
    while (1) {
        int s = rand() % 3 + 1;

        tranca_arquivo();

        FILE *fp = fopen("buffer.txt", "r");
        if (fp == NULL) {
            perror("Erro ao abrir o arquivo");
            destranca_arquivo();
            exit(1);
        }

        int numeros[10];
        int cont = 0;
        while (fscanf(fp, "%d", &numeros[cont]) != EOF) {
            cont++;
        }
        fclose(fp);

        if (cont > 0) {
            printf("[Consumidor] %d\n", numeros[0]);

            fp = fopen("buffer.txt", "w");
            if (fp == NULL) {
                perror("Erro ao abrir o arquivo");
                destranca_arquivo();
                exit(1);
            }

            for (int i = 1; i < cont; i++) {
                fprintf(fp, "%d\n", numeros[i]);
            }

            fclose(fp);
        }

        destranca_arquivo();

        sleep(s);
    }
}

int main() {
    int pid;

    //inicializa o arquivo com valores aleatórios
    inic_buffer();

    pid = fork();
    if (pid < 0) {
        perror("Erro ao criar o processo");
        exit(1);
    }

    if (pid == 0) {
        //processo filho
        consumidor();
    } else {
        //processo pai
        produtor();
    }

    return 0;
}
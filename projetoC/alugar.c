// alugar.c
#include "alugar.h"
#include "filme.h"
#include "cliente.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *fileAluguel;

void menuAlugueis() {
    Aluguel alugueis[MAX_ALUGUEIS];
    int totalAlugueis = 0;

    Cliente clientes[MAX_CLIENTES];
    int totalClientes = 0;

    Filme filmes[MAX_FILMES];
    int totalFilmes = 0;

    int opcao;

    // Carregar dados dos arquivos
    carregarAlugueis(alugueis, &totalAlugueis);
    carregarClientes(clientes, &totalClientes); // Função de cliente.c
    totalFilmes = carregarFilmesDoArquivo(filmes); // Ajuste para usar a função existente

    do {
        printf("\n--- Menu Alugueis ---\n");
        printf("1. Cadastrar Aluguel\n");
        printf("2. Listar Alugueis\n");
        printf("3. Atualizar Aluguel\n");
        printf("4. Apagar Aluguel\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer

        switch(opcao) {
            case 1:
                cadastrarAluguel(alugueis, &totalAlugueis, clientes, totalClientes, filmes, totalFilmes);
                break;
            case 2:
                lerAlugueis(alugueis, totalAlugueis);
                break;
            case 3:
                atualizarAluguel(alugueis, totalAlugueis, clientes, totalClientes, filmes, totalFilmes);
                break;
            case 4:
                apagarAluguel(alugueis, &totalAlugueis);
                break;
            case 0:
                salvarAlugueis(alugueis, totalAlugueis);
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
}

void carregarAlugueis(Aluguel *alugueis, int *totalAlugueis) {
    fileAluguel = fopen("alugueis.txt", "r");
    if (fileAluguel == NULL) {
        *totalAlugueis = 0;
        return;
    }

    *totalAlugueis = 0;
    while (fscanf(fileAluguel, "%d;%d;%d;%[^;];%[^\n]\n",
                  &alugueis[*totalAlugueis].idAluguel,
                  &alugueis[*totalAlugueis].idCliente,
                  &alugueis[*totalAlugueis].idFilme,
                  alugueis[*totalAlugueis].dataAluguel,
                  alugueis[*totalAlugueis].dataDevolucao) != EOF) {
        (*totalAlugueis)++;
    }

    fclose(fileAluguel);
}

void salvarAlugueis(Aluguel *alugueis, int totalAlugueis) {
    fileAluguel = fopen("alugueis.txt", "w");
    if (fileAluguel == NULL) {
        printf("Erro ao abrir o arquivo de alugueis para escrita!\n");
        return;
    }

    for (int i = 0; i < totalAlugueis; i++) {
        fprintf(fileAluguel, "%d;%d;%d;%s;%s\n",
                alugueis[i].idAluguel,
                alugueis[i].idCliente,
                alugueis[i].idFilme,
                alugueis[i].dataAluguel,
                alugueis[i].dataDevolucao);
    }

    fclose(fileAluguel);
}

int clienteExiste(Cliente *clientes, int totalClientes, int idCliente) {
    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].id == idCliente) {
            return 1;
        }
    }
    return 0;
}

int filmeExiste(Filme *filmes, int totalFilmes, int idFilme) {
    for (int i = 0; i < totalFilmes; i++) {
        if (filmes[i].id == idFilme) {
            return 1;
        }
    }
    return 0;
}

int aluguelJaCadastrado(Aluguel *alugueis, int totalAlugueis, int idAluguel) {
    for (int i = 0; i < totalAlugueis; i++) {
        if (alugueis[i].idAluguel == idAluguel) {
            return 1;
        }
    }
    return 0;
}

void cadastrarAluguel(Aluguel *alugueis, int *totalAlugueis, Cliente *clientes, int totalClientes, Filme *filmes, int totalFilmes) {
    if (*totalAlugueis >= MAX_ALUGUEIS) {
        printf("numero maximo de alugueis atingido!\n");
        return;
    }

    Aluguel novoAluguel;
    printf("ID do Aluguel: ");
    scanf("%d", &novoAluguel.idAluguel);
    getchar();

    if (aluguelJaCadastrado(alugueis, *totalAlugueis, novoAluguel.idAluguel)) {
        printf("Aluguel com este ID ja cadastrado!\n");
        return;
    }

    printf("ID do Cliente: ");
    scanf("%d", &novoAluguel.idCliente);
    getchar();

    if (!clienteExiste(clientes, totalClientes, novoAluguel.idCliente)) {
        printf("Cliente nao encontrado!\n");
        return;
    }

    printf("ID do Filme: ");
    scanf("%d", &novoAluguel.idFilme);
    getchar();

    if (!filmeExiste(filmes, totalFilmes, novoAluguel.idFilme)) {
        printf("Filme nao encontrado!\n");
        return;
    }

    printf("Data do Aluguel (DD/MM/AAAA): ");
    fgets(novoAluguel.dataAluguel, sizeof(novoAluguel.dataAluguel), stdin);
    novoAluguel.dataAluguel[strcspn(novoAluguel.dataAluguel, "\n")] = '\0';

    printf("Data de Devolucao (DD/MM/AAAA): ");
    fgets(novoAluguel.dataDevolucao, sizeof(novoAluguel.dataDevolucao), stdin);
    novoAluguel.dataDevolucao[strcspn(novoAluguel.dataDevolucao, "\n")] = '\0';

    alugueis[*totalAlugueis] = novoAluguel;
    (*totalAlugueis)++;
    printf("Aluguel cadastrado com sucesso!\n");
}

void lerAlugueis(Aluguel *alugueis, int totalAlugueis) {
    for (int i = 0; i < totalAlugueis; i++) {
        printf("\nID Aluguel: %d\n", alugueis[i].idAluguel);
        printf("ID Cliente: %d\n", alugueis[i].idCliente);
        printf("ID Filme: %d\n", alugueis[i].idFilme);
        printf("Data Aluguel: %s\n", alugueis[i].dataAluguel);
        printf("Data Devolucao: %s\n", alugueis[i].dataDevolucao);
    }
}

void atualizarAluguel(Aluguel *alugueis, int totalAlugueis, Cliente *clientes, int totalClientes, Filme *filmes, int totalFilmes) {
    int idAluguel;
    printf("ID do Aluguel a ser atualizado: ");
    scanf("%d", &idAluguel);
    getchar();

    int index = -1;
    for (int i = 0; i < totalAlugueis; i++) {
        if (alugueis[i].idAluguel == idAluguel) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Aluguel com ID %d nao encontrado!\n", idAluguel);
        return;
    }

    Aluguel *aluguel = &alugueis[index];

    printf("Novo ID do Cliente: ");
    scanf("%d", &aluguel->idCliente);
    getchar();

    if (!clienteExiste(clientes, totalClientes, aluguel->idCliente)) {
        printf("Cliente nao encontrado!\n");
        return;
    }

    printf("Novo ID do Filme: ");
    scanf("%d", &aluguel->idFilme);
    getchar();

    if (!filmeExiste(filmes, totalFilmes, aluguel->idFilme)) {
        printf("Filme nao encontrado!\n");
        return;
    }

    printf("Nova Data do Aluguel (DD/MM/AAAA): ");
    fgets(aluguel->dataAluguel, sizeof(aluguel->dataAluguel), stdin);
    aluguel->dataAluguel[strcspn(aluguel->dataAluguel, "\n")] = '\0';

    printf("Nova Data de Devolucao (DD/MM/AAAA): ");
    fgets(aluguel->dataDevolucao, sizeof(aluguel->dataDevolucao), stdin);
    aluguel->dataDevolucao[strcspn(aluguel->dataDevolucao, "\n")] = '\0';

    printf("Aluguel atualizado com sucesso!\n");
}

void apagarAluguel(Aluguel *alugueis, int *totalAlugueis) {
    int idAluguel;
    printf("ID do Aluguel a ser apagado: ");
    scanf("%d", &idAluguel);
    getchar();

    int index = -1;
    for (int i = 0; i < *totalAlugueis; i++) {
        if (alugueis[i].idAluguel == idAluguel) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Aluguel com ID %d nao encontrado!\n", idAluguel);
        return;
    }

    for (int i = index; i < *totalAlugueis - 1; i++) {
        alugueis[i] = alugueis[i + 1];
    }

    (*totalAlugueis)--;
    printf("Aluguel apagado com sucesso!\n");
}


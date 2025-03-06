#include "endereco.h"
#include <string.h>
#include <stdlib.h>

// Inicialização da variável global do arquivo
FILE *file;

void menuEnderecos() {
    Endereco enderecos[MAX_ENDERECOS];
    int totalEnderecos = 0;
    int opcao;


    carregarEnderecos(enderecos, &totalEnderecos);

    do {
        // Menu de Endereços
        printf("======== Menu Enderecos ========\n");
        printf("1. Cadastrar Endereco\n");
        printf("2. Listar Enderecos\n");
        printf("3. Atualizar Endereco\n");
        printf("4. Excluir Endereco\n");
        printf("5. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarEndereco(enderecos, &totalEnderecos);
                break;
            case 2:
                listarEnderecos(enderecos, totalEnderecos);
                break;
            case 3:
                atualizarEndereco(enderecos, totalEnderecos);
                break;
            case 4:
                excluirEndereco(enderecos, &totalEnderecos);
                break;
            case 5:
                salvarEnderecos(enderecos, totalEnderecos);
                printf("Enderecos salvos. Saindo.\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 5); // Voltar ao menu principal
}

// Função para carregar endereços do arquivo
void carregarEnderecos(Endereco *enderecos, int *totalEnderecos) {
    file = fopen(ARQUIVO_ENDERECO, "r");
    if (file != NULL) {
        *totalEnderecos = 0;
        while (fscanf(file, "%99[^\n]\n%d\n%49[^\n]\n%49[^\n]\n%29[^\n]\n%9[^\n]\n",
                      enderecos[*totalEnderecos].rua,
                      &enderecos[*totalEnderecos].numero,
                      enderecos[*totalEnderecos].bairro,
                      enderecos[*totalEnderecos].cidade,
                      enderecos[*totalEnderecos].estado,
                      enderecos[*totalEnderecos].cep) == 6) {
            (*totalEnderecos)++;
        }
        fclose(file);
    } else {
        printf("Arquivo nao encontrado. Sera criado ao salvar.\n");
    }
}

// Função para salvar endereços no arquivo
void salvarEnderecos(Endereco *enderecos, int totalEnderecos) {
    file = fopen(ARQUIVO_ENDERECO, "w");
    if (file != NULL) {
        for (int i = 0; i < totalEnderecos; i++) {
            fprintf(file, "%s\n%d\n%s\n%s\n%s\n%s\n",
                    enderecos[i].rua,
                    enderecos[i].numero,
                    enderecos[i].bairro,
                    enderecos[i].cidade,
                    enderecos[i].estado,
                    enderecos[i].cep);
        }
        fclose(file);
    } else {
        printf("Erro ao salvar o arquivo.\n");
    }
}

// Função para cadastrar um novo endereço
void cadastrarEndereco(Endereco *enderecos, int *totalEnderecos) {
    if (*totalEnderecos >= MAX_ENDERECOS) {
        printf("Limite maximo de enderecos atingido.\n");
        return;
    }

    Endereco novo;
    printf("Rua: ");
    scanf(" %[^\n]", novo.rua);
    printf("Numero: ");
    scanf("%d", &novo.numero);
    printf("Bairro: ");
    scanf(" %[^\n]", novo.bairro);
    printf("Cidade: ");
    scanf(" %[^\n]", novo.cidade);
    printf("Estado: ");
    scanf(" %[^\n]", novo.estado);
    printf("CEP: ");
    scanf(" %[^\n]", novo.cep);

    enderecos[*totalEnderecos] = novo;
    (*totalEnderecos)++;
    printf("Endereco cadastrado com sucesso!\n");
}

// Função para ler e exibir todos os endereços cadastrados
void listarEnderecos(Endereco *enderecos, int totalEnderecos) {
    if (totalEnderecos == 0) {
        printf("Nenhum endereco cadastrado.\n");
        return;
    }

    printf("=== Lista de Enderecos ===\n");
    for (int i = 0; i < totalEnderecos; i++) {
        printf("Endereco %d:\n", i + 1);
        printf("  Rua: %s\n", enderecos[i].rua);
        printf("  Numero: %d\n", enderecos[i].numero);
        printf("  Bairro: %s\n", enderecos[i].bairro);
        printf("  Cidade: %s\n", enderecos[i].cidade);
        printf("  Estado: %s\n", enderecos[i].estado);
        printf("  CEP: %s\n", enderecos[i].cep);
        printf("--------------------------\n");
    }
}

// Função para atualizar um endereço específico
void atualizarEndereco(Endereco *enderecos, int totalEnderecos) {
    int index;
    printf("Digite o numero do endereco a atualizar (1-%d): ", totalEnderecos);
    scanf("%d", &index);

    if (index < 1 || index > totalEnderecos) {
        printf("Endereco invalido.\n");
        return;
    }

    Endereco *endereco = &enderecos[index - 1];
    printf("Atualizando o endereco:\n");
    printf("Caso queira manter o endereco, repita o mesmo\n");

    printf("Rua (%s): ", endereco->rua);
    scanf(" %[^\n]", endereco->rua);
    printf("Numero (%d): ", endereco->numero);
    scanf("%d", &endereco->numero);
    printf("Bairro (%s): ", endereco->bairro);
    scanf(" %[^\n]", endereco->bairro);
    printf("Cidade (%s): ", endereco->cidade);
    scanf(" %[^\n]", endereco->cidade);
    printf("Estado (%s): ", endereco->estado);
    scanf(" %[^\n]", endereco->estado);
    printf("CEP (%s): ", endereco->cep);
    scanf(" %[^\n]", endereco->cep);

    printf("Endereco atualizado com sucesso!\n");
}

// Função para excluir um endereço específico
void excluirEndereco(Endereco *enderecos, int *totalEnderecos) {
    int index;
    printf("Digite o numero do endereco a excluir (1-%d): ", *totalEnderecos);
    scanf("%d", &index);

    if (index < 1 || index > *totalEnderecos) {
        printf("Endereco invalido.\n");
        return;
    }

    for (int i = index - 1; i < *totalEnderecos - 1; i++) {
        enderecos[i] = enderecos[i + 1];
    }
    (*totalEnderecos)--;  // Decrementa o total de endereços
    printf("Endereco excluido com sucesso!\n");
}


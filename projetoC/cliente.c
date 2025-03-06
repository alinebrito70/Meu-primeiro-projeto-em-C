#include "cliente.h"
#include <stdio.h>
#include <string.h>

// Inicializacao da variavel global do arquivo
FILE *file;

void menuClientes() {
    Cliente clientes[MAX_CLIENTES];
    int totalClientes = 0;
    int opcao;

    // Carregar os clientes do arquivo ao abrir o menu
    carregarClientes(clientes, &totalClientes);

    do {
        // Menu de Clientes
        printf("======== Menu de Clientes ========\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Listar Clientes\n");
        printf("3. Atualizar Cliente\n");
        printf("4. Apagar Cliente\n");
        printf("5. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCliente(clientes, &totalClientes);
                salvarClientes(clientes, totalClientes);  // Salva apos cadastro
                break;
            case 2:
                lerClientes(clientes, totalClientes);
                break;
            case 3:
                atualizarCliente(clientes, totalClientes);
                salvarClientes(clientes, totalClientes);  // Salva apos atualizacao
                break;
            case 4:
                apagarCliente(clientes, &totalClientes);
                salvarClientes(clientes, totalClientes);  // Salva apos apagar
                break;
            case 5:
                printf("Salvando dados e voltando ao menu principal...\n");
                salvarClientes(clientes, totalClientes);  // Salva antes de sair
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 5); // Voltar ao menu principal
}

// Carrega os clientes do arquivo
void carregarClientes(Cliente *clientes, int *totalClientes) {
    file = fopen("cliente.txt", "r");
    if (file != NULL) {
        *totalClientes = 0;
        while (fscanf(file, "%49[^\n]\n%99[^\n]\n%19[^\n]\n%d\n", 
                      clientes[*totalClientes].nome, 
                      clientes[*totalClientes].endereco, 
                      clientes[*totalClientes].telefone, 
                      &clientes[*totalClientes].id) == 4) {
            (*totalClientes)++;
        }
        fclose(file);
        file = NULL;
    } else {
        printf("Arquivo nao encontrado. Um novo sera criado ao salvar.\n");
    }
}

// Salva os clientes no arquivo
void salvarClientes(Cliente *clientes, int totalClientes) {
    file = fopen("cliente.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < totalClientes; i++) {
            fprintf(file, "%s\n%s\n%s\n%d\n", 
                    clientes[i].nome, 
                    clientes[i].endereco, 
                    clientes[i].telefone, 
                    clientes[i].id);
        }
        fclose(file);
        file = NULL;
    } else {
        printf("Erro ao salvar o arquivo de clientes.\n");
    }
}

// Verifica se o cliente ja esta cadastrado
int clienteJaCadastrado(Cliente *clientes, int totalClientes, const char *nome, int id) {
    for (int i = 0; i < totalClientes; i++) {
        if (strcmp(clientes[i].nome, nome) == 0 || clientes[i].id == id) {
            return 1;
        }
    }
    return 0;
}

// Cadastra um novo cliente
void cadastrarCliente(Cliente *clientes, int *totalClientes) {
    if (*totalClientes >= MAX_CLIENTES) {
        printf("Limite maximo de clientes atingido.\n");
        return;
    }

    Cliente novoCliente;
    printf("Nome do cliente: ");
    scanf(" %[^\n]", novoCliente.nome);
    printf("Endereco: ");
    scanf(" %[^\n]", novoCliente.endereco);
    printf("Telefone: ");
    scanf(" %[^\n]", novoCliente.telefone);
    printf("ID: ");
    scanf("%d", &novoCliente.id);

    if (clienteJaCadastrado(clientes, *totalClientes, novoCliente.nome, novoCliente.id)) {
        printf("Cliente ja cadastrado.\n");
        return;
    }

    clientes[*totalClientes] = novoCliente;
    (*totalClientes)++;
    printf("Cliente cadastrado com sucesso.\n");
}

// Exibe a lista de clientes de forma organizada
void lerClientes(Cliente *clientes, int totalClientes) {
    if (totalClientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    printf("=== Lista de Clientes Cadastrados ===\n");
    for (int i = 0; i < totalClientes; i++) {
        printf("Cliente %d:\n", i + 1);
        printf("  Nome:      %s\n", clientes[i].nome);
        printf("  Endereco:  %s\n", clientes[i].endereco);
        printf("  Telefone:  %s\n", clientes[i].telefone);
        printf("  ID:        %d\n", clientes[i].id);
        printf("-------------------------------------\n");
    }
}

// Atualiza as informacoes de um cliente
void atualizarCliente(Cliente *clientes, int totalClientes) {
    int id;
    printf("Informe o ID do cliente para atualizar: ");
    scanf("%d", &id);

    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].id == id) {
            printf("Novo nome: ");
            scanf(" %[^\n]", clientes[i].nome);
            printf("Novo endereco: ");
            scanf(" %[^\n]", clientes[i].endereco);
            printf("Novo telefone: ");
            scanf(" %[^\n]", clientes[i].telefone);
            printf("Atualizacao realizada.\n");
            return;
        }
    }
    printf("Cliente nao encontrado.\n");
}

// Apaga um cliente
void apagarCliente(Cliente *clientes, int *totalClientes) {
    int id;
    printf("Informe o ID do cliente para apagar: ");
    scanf("%d", &id);

    for (int i = 0; i < *totalClientes; i++) {
        if (clientes[i].id == id) {
            for (int j = i; j < *totalClientes - 1; j++) {
                clientes[j] = clientes[j + 1];
            }
            (*totalClientes)--; // Decrementa o total de clientes
            printf("Cliente apagado com sucesso.\n");
            return;
        }
    }
    printf("Cliente nao encontrado.\n");
}


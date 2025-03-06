#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>

#define MAX_CLIENTES 100  // Definindo o limite m�ximo de clientes

// Estrutura Cliente
typedef struct Cliente {
    char nome[50];
    char endereco[100];  // Endere�o do cliente
    char telefone[20];   // Telefone do cliente
    int id;
} Cliente;

// Vari�vel global para o arquivo
extern FILE *file; // Declara��o global do arquivo
void menuClientes();
// Declara��es das fun��es
void cadastrarCliente(Cliente *clientes, int *totalClientes);
void lerClientes(Cliente *clientes, int totalClientes);
void atualizarCliente(Cliente *clientes, int totalClientes);
void apagarCliente(Cliente *clientes, int *totalClientes);
int clienteJaCadastrado(Cliente *clientes, int totalClientes, const char *nome, int id);
void carregarClientes(Cliente *clientes, int *totalClientes);
void salvarClientes(Cliente *clientes, int totalClientes);


#endif // CLIENTE_H


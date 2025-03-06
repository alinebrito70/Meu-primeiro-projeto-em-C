#ifndef ENDERECO_H
#define ENDERECO_H

#include <stdio.h>

#define MAX_ENDERECOS 100
#define ARQUIVO_ENDERECO "enderecos.txt"

// Declara��o da vari�vel global
extern FILE *file;

// Estrutura de Endere�o
typedef struct Endereco {
    char rua[100];
    int numero;
    char bairro[50];
    char cidade[50];
    char estado[30];
    char cep[10];
} Endereco;
void menuEnderecos();
// Fun��es
void carregarEnderecos(Endereco *enderecos, int *totalEnderecos);
void salvarEnderecos(Endereco *enderecos, int totalEnderecos);
void cadastrarEndereco(Endereco *enderecos, int *totalEnderecos);
void listarEnderecos(Endereco *enderecos, int totalEnderecos);
void atualizarEndereco(Endereco *enderecos, int totalEnderecos);
void excluirEndereco(Endereco *enderecos, int *totalEnderecos);


#endif // ENDERECO_H


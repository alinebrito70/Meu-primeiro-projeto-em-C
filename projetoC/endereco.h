#ifndef ENDERECO_H
#define ENDERECO_H

#include <stdio.h>

#define MAX_ENDERECOS 100
#define ARQUIVO_ENDERECO "enderecos.txt"

// Declaração da variável global
extern FILE *file;

// Estrutura de Endereço
typedef struct Endereco {
    char rua[100];
    int numero;
    char bairro[50];
    char cidade[50];
    char estado[30];
    char cep[10];
} Endereco;
void menuEnderecos();
// Funções
void carregarEnderecos(Endereco *enderecos, int *totalEnderecos);
void salvarEnderecos(Endereco *enderecos, int totalEnderecos);
void cadastrarEndereco(Endereco *enderecos, int *totalEnderecos);
void listarEnderecos(Endereco *enderecos, int totalEnderecos);
void atualizarEndereco(Endereco *enderecos, int totalEnderecos);
void excluirEndereco(Endereco *enderecos, int *totalEnderecos);


#endif // ENDERECO_H


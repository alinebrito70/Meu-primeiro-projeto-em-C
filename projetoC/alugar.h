// alugar.h
#ifndef ALUGAR_H
#define ALUGAR_H

#include <stdio.h>
#include "cliente.h"
#include "filme.h"

#define MAX_ALUGUEIS 200  // Definindo o limite m�ximo de alugueis

// Estrutura Aluguel
typedef struct Aluguel {
    int idAluguel;            // ID do aluguel
    int idCliente;            // ID do cliente
    int idFilme;              // ID do filme alugado
    char dataAluguel[11];     // Data do aluguel (formato: DD/MM/AAAA)
    char dataDevolucao[11];   // Data prevista para devolu��o (formato: DD/MM/AAAA)
} Aluguel;

// Vari�vel global para o arquivo
extern FILE *fileAluguel; // Declara��o global do arquivo para alugueis

void menuAlugueis();

// Declara��es das fun��es
void cadastrarAluguel(Aluguel *alugueis, int *totalAlugueis, Cliente *clientes, int totalClientes, Filme *filmes, int totalFilmes);
void lerAlugueis(Aluguel *alugueis, int totalAlugueis);
void atualizarAluguel(Aluguel *alugueis, int totalAlugueis, Cliente *clientes, int totalClientes, Filme *filmes, int totalFilmes);
void apagarAluguel(Aluguel *alugueis, int *totalAlugueis);
int aluguelJaCadastrado(Aluguel *alugueis, int totalAlugueis, int idAluguel);
void carregarAlugueis(Aluguel *alugueis, int *totalAlugueis);
void salvarAlugueis(Aluguel *alugueis, int totalAlugueis);
int clienteExiste(Cliente *clientes, int totalClientes, int idCliente);
int filmeExiste(Filme *filmes, int totalFilmes, int idFilme);

#endif // ALUGAR_H


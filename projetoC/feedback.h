#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <stdio.h>

#define MAXFEEDBACKS 100
#define ARQUIVO_FEEDBACK "feedbacks.txt"  // Nome do arquivo de texto

typedef struct {
    int id;                
    int id_cliente;        
    int id_filme;          
    char comentario[255];  
    float avaliacao;         
} Feedback;

// Funções CRUD para Feedback
void carregarFeedbacks();                  // Carrega feedbacks do arquivo
void salvarFeedbacks();                    // Salva feedbacks no arquivo
void adicionarFeedback(Feedback novo);     // Adiciona e salva novo feedback
void listarFeedbacks();                    // Lista todos os feedbacks
void buscarFeedbackPorCliente(int id_cliente); // Busca feedbacks por cliente
void atualizarFeedback(int id);            // Atualiza feedback existente
void excluirFeedback(int id);              // Exclui feedback pelo ID
void menuFeedback();                               // Exibe o menu principal

#endif


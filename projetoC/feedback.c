#include "feedback.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Feedback feedbacks[MAXFEEDBACKS];
int total_feedbacks = 0;
int prox_id = 1;

void menuFeedback() {
    int opcao;
    carregarFeedbacks();

    do {
        printf("\n--- Sistema de Feedback de Clientes ---\n");
        printf("1. Adicionar Feedback\n");
        printf("2. Listar Feedbacks\n");
        printf("3. Buscar Feedback por Cliente\n");
        printf("4. Atualizar Feedback\n");
        printf("5. Excluir Feedback\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            Feedback novo;
            printf("ID do Cliente: ");
            scanf("%d", &novo.id_cliente);
            printf("ID do Filme: ");
            scanf("%d", &novo.id_filme);
            printf("Avaliacao (1 a 5): ");
            scanf("%f", &novo.avaliacao);
            getchar();
            printf("Comentario: ");
            fgets(novo.comentario, sizeof(novo.comentario), stdin);
            strtok(novo.comentario, "\n"); // Remove o '\n' do final
            adicionarFeedback(novo);

        } else if (opcao == 2) {
            listarFeedbacks();

        } else if (opcao == 3) {
            int id_cliente;
            printf("Informe o ID do Cliente: ");
            scanf("%d", &id_cliente);
            buscarFeedbackPorCliente(id_cliente);

        } else if (opcao == 4) {
            int id;
            printf("Informe o ID do Feedback para atualizar: ");
            scanf("%d", &id);
            atualizarFeedback(id);

        } else if (opcao == 5) {
            int id;
            printf("Informe o ID do Feedback para excluir: ");
            scanf("%d", &id);
            excluirFeedback(id);

        } else if (opcao == 6) {
            printf("Saindo de feedback...\n");
            salvarFeedbacks();
		

        } else {
            printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 6);
}

void carregarFeedbacks() {
    FILE *file = fopen(ARQUIVO_FEEDBACK, "r");
    if (file != NULL) {
        total_feedbacks = 0; // Reinicia a contagem
        while (fscanf(file, "%d %d %d %f %[^\n]",
                      &feedbacks[total_feedbacks].id,
                      &feedbacks[total_feedbacks].id_cliente,
                      &feedbacks[total_feedbacks].id_filme,
                      &feedbacks[total_feedbacks].avaliacao,
                      feedbacks[total_feedbacks].comentario) == 5) {
            total_feedbacks++;
        }
        if (total_feedbacks > 0) {
            prox_id = feedbacks[total_feedbacks - 1].id + 1;
        }
        fclose(file);
    }
}

void salvarFeedbacks() {
    FILE *file = fopen(ARQUIVO_FEEDBACK, "w");
    int i;
    if (file != NULL) {
        for (i = 0; i < total_feedbacks; i++) {
            fprintf(file, "%d %d %d %.1f %s\n",
                    feedbacks[i].id, feedbacks[i].id_cliente,
                    feedbacks[i].id_filme, feedbacks[i].avaliacao,
                    feedbacks[i].comentario);
        }
        fclose(file);
    } else {
        printf("Erro ao salvar feedbacks no arquivo.\n");
    }
}

void adicionarFeedback(Feedback novo) {
    if (total_feedbacks < MAXFEEDBACKS) {
        novo.id = prox_id++;
        feedbacks[total_feedbacks++] = novo;
        salvarFeedbacks();
        printf("Feedback adicionado com sucesso! ID do Feedback: %d\n", novo.id);
    } else {
        printf("Erro: limite maximo de feedbacks atingido.\n");
    }
}

void listarFeedbacks() {
	int i;
    if (total_feedbacks == 0) {
        printf("Nenhum feedback registrado.\n");
        return;
    }

    for ( i = 0; i < total_feedbacks; i++) {
    printf("  ID:          %d\n", feedbacks[i].id);
    printf("  Cliente ID:  %d\n", feedbacks[i].id_cliente);
    printf("  Filme ID:    %d\n", feedbacks[i].id_filme);
    printf("  Avaliacao:   %.1f\n", feedbacks[i].avaliacao);
    printf("  Comentario:  %s\n", feedbacks[i].comentario);
    printf("-------------------------------------\n");
}

    }

void buscarFeedbackPorCliente(int id_cliente) {
    int encontrado = 0,i;

    for ( i = 0; i < total_feedbacks; i++) {
        if (feedbacks[i].id_cliente == id_cliente) {
            printf("ID: %d | Filme ID: %d | Avaliacao: %.1f | Comentario: %s\n",
                   feedbacks[i].id, feedbacks[i].id_filme,
                   feedbacks[i].avaliacao, feedbacks[i].comentario);
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("Nenhum feedback encontrado para o cliente ID %d.\n", id_cliente);
    }
}

void atualizarFeedback(int id) {
    int encontrado = 0,i;

    for ( i = 0; i < total_feedbacks; i++) {
        if (feedbacks[i].id == id) {
            printf("Novo ID do Cliente: ");
            scanf("%d", &feedbacks[i].id_cliente);
            printf("Novo ID do Filme: ");
            scanf("%d", &feedbacks[i].id_filme);
            printf("Nova Avaliacao (1 a 5): ");
            scanf("%f", &feedbacks[i].avaliacao);
            getchar();
            printf("Novo Comentario: ");
            fgets(feedbacks[i].comentario, sizeof(feedbacks[i].comentario), stdin);
            strtok(feedbacks[i].comentario, "\n");
            salvarFeedbacks();
            printf("Feedback atualizado com sucesso!\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Feedback com ID %d nao encontrado.\n", id);
    }
}

void excluirFeedback(int id) {
    int encontrado = 0,i,j;

    for ( i = 0; i < total_feedbacks; i++) {
        if (feedbacks[i].id == id) {
            for ( j = i; j < total_feedbacks - 1; j++) {
                feedbacks[j] = feedbacks[j + 1];
            }
            total_feedbacks--;
            salvarFeedbacks();
            printf("Feedback com ID %d excluido com sucesso.\n", id);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Feedback com ID %d nao encontrado.\n", id);
    }
}


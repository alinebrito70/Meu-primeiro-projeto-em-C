#include <stdio.h>
#include "filme.h"
#include "cliente.h"
#include "endereco.h"
#include "feedback.h"

int main() {
    int opcao;

	
    do {

        // Menu principal
        printf("======== Menu Principal ========\n");
        printf("1. Filmes\n");
        printf("2. Clientes\n");
        printf("3. Enderecos\n");
        printf("4. Feedback\n");  // Nova opção de Feedback
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                menuFilmes();  // Chama o menu de Filmes
                break;
            case 2:
                menuClientes();  // Chama o menu de Clientes
                break;
            case 3:
                menuEnderecos();  // Chama o menu de Endereços
                break;
            case 4:
                menuFeedback();  // Chama o menu de Feedback
                break;
            case 5:
                printf("Saindo... Ate logo!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 5); // Sai do programa

    return 0;
}

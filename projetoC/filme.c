#include <stdio.h>
#include <string.h>
#include "filme.h"

void menuFilmes() {
    Filme filme[MAX_FILMES];
    int totalFilmes = 0;
    int opcao;

    do {
        printf("\n======== Menu Filmes ========\n");
        printf("1. Cadastrar filme\n");
        printf("2. Apagar filme\n");
        printf("3. Atualizar filme\n");
        printf("4. Listar filmes\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrarFilme(filme, &totalFilmes);
                break;
            case 2:
                apagarFilme(filme, &totalFilmes);
                break;
            case 3:
                atualizarFilme(filme, &totalFilmes);
                break;
            case 4:
                listarFilmes();
                break;
            case 5:
                printf("Fechando...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 5);
}

FILE *abrirArquivo(const char *nomeArquivo, const char *modo) {
    FILE *arquivofilme = fopen(nomeArquivo, modo);
    if (arquivofilme == NULL) {
        printf("Erro ao abrir o arquivo %s com modo %s\n", nomeArquivo, modo);
    }
    return arquivofilme;
}

int carregarFilmesDoArquivo(Filme *filmes) {
    FILE *arquivofilme = abrirArquivo("filmes.txt", "r");
    int totalFilmes = 0;

    while (fscanf(arquivofilme, "Nome: %49[^,], ID: %d, Genero: %19[^,], Preco: %f\n",filmes[totalFilmes].nome, &filmes[totalFilmes].id,filmes[totalFilmes].genero, &filmes[totalFilmes].preco) == 4) {
        totalFilmes++;
        if (totalFilmes >= MAX_FILMES) {
            break; // Respeita o limite de filmes
        }
    }

    fclose(arquivofilme);
    return totalFilmes;
}

void cadastrarFilme(Filme *filme, int *totaldefilmes) {
    Filme novoFilme;
    *totaldefilmes = carregarFilmesDoArquivo(filme);

    char parar;
    
    do {
    	
    if (*totaldefilmes >= MAX_FILMES) {
        printf("Limite de filmes atingido!\n");
        return;
    }

        FILE *arquivofilme = abrirArquivo("filmes.txt", "a"); // Abre o arquivo para gravação
        if (arquivofilme == NULL) {
            return;
        }

        printf("Insira o nome: ");
        	scanf(" %49[^\n]s", novoFilme.nome);

        printf("Insira o ID do filme: ");
        	scanf("%d", &novoFilme.id);

        printf("Insira o genero do filme: ");
        	scanf(" %19[^\n]s", novoFilme.genero);

        printf("Insira o preco do filme: ");
        	scanf("%f", &novoFilme.preco);

        if (filmeJaCadastrado(filme, *totaldefilmes, novoFilme.nome, novoFilme.id) == 1) {
            printf("Erro: Filme com nome \"%s\" ou ID \"%d\" ja cadastrado!\n", novoFilme.nome, novoFilme.id);
            fclose(arquivofilme);
            return;
        }

        filme[*totaldefilmes] = novoFilme;
        (*totaldefilmes)++;

        fprintf(arquivofilme, "Nome: %s, ID: %d, Genero: %s, Preco: %.2f\n", novoFilme.nome, novoFilme.id, novoFilme.genero, novoFilme.preco);

        printf("=== Filme Cadastrado ===\n");
		printf("  Nome:      %s\n", novoFilme.nome);
		printf("  ID:        %d\n", novoFilme.id);
		printf("  Genero:    %s\n", novoFilme.genero);
		printf("  Preco:     R$ %.2f\n", novoFilme.preco);
		printf("-------------------------------------\n");
		
        printf("Deseja cadastrar outro filme? [S-SIM|N-NAO]: ");
        fflush(stdin);
        scanf("%c", &parar);

        fclose(arquivofilme);

    } while (parar == 'S' || parar == 's');
}


int filmeJaCadastrado(Filme *filme, int totaldefilmes, const char *nome, int id) {
    FILE *arquivofilme = abrirArquivo("filmes.txt", "r");
    if (arquivofilme != NULL) {
        Filme filmeArquivo;
        while (fscanf(arquivofilme, "Nome: %49[^,], ID: %d, Genero: %19[^,], Preco: %f\n", filmeArquivo.nome, &filmeArquivo.id, filmeArquivo.genero, &filmeArquivo.preco) == 4) {
            if (strcmp(filmeArquivo.nome, nome) == 0 || filmeArquivo.id == id) {
                fclose(arquivofilme);
                return 1;
            }
        }
        fclose(arquivofilme);
    }
    return 0;
}

void apagarFilme(Filme *filme, int *totalFilmes) {
    int id, encontrado = 0;
    Filme tempFilme;
    printf("==========================================\n");
    printf("Insira o ID do filme que deseja apagar: ");
    printf("\n==========================================\n");
    scanf("%d", &id);

    FILE *arquivofilme = abrirArquivo("filmes.txt", "r");
    if (arquivofilme == NULL) {
        return;
    }

    FILE *arquivoTemp = abrirArquivo("temp_filmes.txt", "w");
    if (arquivoTemp == NULL) {
        fclose(arquivofilme);
        return;
    }

    while (fscanf(arquivofilme, "Nome: %49[^,], ID: %d, Genero: %19[^,], Preco: %f\n", tempFilme.nome, &tempFilme.id, tempFilme.genero, &tempFilme.preco) == 4) {
        if (tempFilme.id == id) {
            encontrado = 1;
            printf("==========================================\n");
            printf("Filme com ID %d apagado com sucesso!\n", id);
            printf("==========================================\n");
            continue; // Não copia o filme apagado para o arquivo temporário
        }
        fprintf(arquivoTemp, "Nome: %s, ID: %d, Genero: %s, Preco: %.2f\n", tempFilme.nome, tempFilme.id, tempFilme.genero, tempFilme.preco);
    }

    fclose(arquivofilme);
    fclose(arquivoTemp);

    if (!encontrado) {
        printf("==========================================\n");
        printf("Filme com ID %d nao encontrado.\n", id);
        printf("==========================================\n");
        remove("temp_filmes.txt");
        return;
    }

    // Atualiza o arquivo original e o array de filmes
    remove("filmes.txt");
    rename("temp_filmes.txt", "filmes.txt");

    // Recarrega os filmes do arquivo para o array e decrementa o total
    *totalFilmes = carregarFilmesDoArquivo(filme);
}


void atualizarFilme(Filme *filme, int *totalFilmes) {
    int id, encontrado = 0, i, j;
    Filme tempFilme;
    Filme filmesNoArquivo[100];
    int contadorFilmes = 0;
	printf("==========================================\n");
    printf("Insira o ID do filme que deseja atualizar: ");
    printf("\n==========================================\n");
    scanf("%d", &id);

    FILE *arquivofilme = abrirArquivo("filmes.txt", "r"); // R para leitura no arquivo
    if (arquivofilme == NULL) {
        return;
    }

    while (fscanf(arquivofilme, "Nome: %49[^,], ID: %d, Genero: %19[^,], Preco: %f\n", filmesNoArquivo[contadorFilmes].nome, &filmesNoArquivo[contadorFilmes].id, filmesNoArquivo[contadorFilmes].genero, &filmesNoArquivo[contadorFilmes].preco) == 4) {
        contadorFilmes++;
    }
    fclose(arquivofilme);

    for (i = 0; i < contadorFilmes; i++) {
        if (filmesNoArquivo[i].id == id) {
            encontrado = 1;
			printf("=====Filme encontrado=====\n");
            printf("\nFilme encontrado:\n");
            printf("Nome: %s, ID: %d, Genero: %s, Preco: %.2f\n", filmesNoArquivo[i].nome, filmesNoArquivo[i].id, filmesNoArquivo[i].genero, filmesNoArquivo[i].preco);
			printf("--------------------------\n");


            printf("Insira o novo nome: ");
            	scanf(" %[^\n]s", filmesNoArquivo[i].nome);

            printf("Insira o novo ID: ");
            	scanf("%d", &filmesNoArquivo[i].id);

            printf("Insira o novo genero: ");
            	scanf(" %[^\n]s", filmesNoArquivo[i].genero);

            printf("Insira o novo preco: ");
            	scanf("%f", &filmesNoArquivo[i].preco);
             printf("----------------------------\n");
            break;
        }
    }

    if (!encontrado) {
    	printf("----------------------------\n");
        printf("Filme com ID %d nao encontrado.\n", id);
        printf("----------------------------\n");
        return;
    }

    arquivofilme = abrirArquivo("filmes.txt", "w"); //W para escrever no arquivo
    if (arquivofilme == NULL) {
        return;
    }

    for (i = 0; i < contadorFilmes; i++) {
        fprintf(arquivofilme, "Nome: %s, ID: %d, Genero: %s, Preco: %.2f\n", filmesNoArquivo[i].nome, filmesNoArquivo[i].id, filmesNoArquivo[i].genero, filmesNoArquivo[i].preco);
    }

    fclose(arquivofilme);
    printf("Filme atualizado com sucesso!\n");
    printf("----------------------------\n");
}

void listarFilmes(){
    Filme filme;
    int i = 0;

    FILE *arquivofilme = abrirArquivo("filmes.txt", "r"); //R para leitura no arquivo
    if (arquivofilme == NULL) {
        return;
    }
	printf("=====Lista de Filmes Cadastrados=====\n");
   

    while (fscanf(arquivofilme, "Nome: %49[^,], ID: %d, Genero: %19[^,], Preco: %f\n", filme.nome, &filme.id, filme.genero, &filme.preco) == 4) {
        printf("Nome: %s\n", filme.nome);
        printf("ID: %d\n", filme.id);
        printf("Genero: %s\n", filme.genero);
        printf("Preco: %.2f\n", filme.preco);
        printf("-------------------------\n");
        i++;
    }

    if (i == 0) {
        printf("Nenhum filme cadastrado.\n");
    }

    fclose(arquivofilme);
}


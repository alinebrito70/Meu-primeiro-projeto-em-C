#ifndef FILME_H
#define FILME_H
#define MAX_FILMES 100

typedef struct Filme{
    char nome[50];
    char genero[20];
    int id;
    float preco;

}Filme;

extern FILE *arquivofilme;

FILE *abrirArquivo(const char *nomeArquivo, const char *modo);

void menuFilmes();

void cadastrarFilme(Filme *filme, int *totaldefilmes);

int carregarFilmesDoArquivo(Filme *filmes);

int filmeJaCadastrado(Filme *filme, int totaldefilmes, const char *nomedofilme, int id);

void apagarFilme(Filme *filme, int *totaldefilmes);

void atualizarFilme(Filme *filme, int *totalFilmes);

void listarFilmes();

#endif // FILME_H


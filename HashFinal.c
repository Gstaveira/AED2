#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TABLE_SIZE 2000

//Estrututra do nó
typedef struct Node {
    int chave;
    struct Node *prox;
} Node;

//Tabela de nós
typedef struct {
    Node *lista;
} TabelaHash;

// Função hash primária multiplicativa
unsigned int hash1(int key) {
    double parte_frac = key * ((sqrt(5) - 1) / 2) - (int)(key * ((sqrt(5) - 1) / 2));
    return (unsigned int)(TABLE_SIZE * parte_frac);
}

// Função para inicializar a tabela hash
void inicializaTabela(TabelaHash tabela[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        tabela[i].lista = NULL; // Inicializa cada lista encadeada como vazia
    }
}

// Função para inserir uma chave na tabela hash usando encadeamento separado
void insere(TabelaHash tabela[], int chave) {
    unsigned int indice = hash1(chave);

    Node *novo = (Node *)malloc(sizeof(Node));
    if (novo == NULL) {
        printf("Erro: nao foi possível alocar memória.\n");
        exit(1);
    }
    novo->chave = chave;
    novo->prox = NULL;

    if (tabela[indice].lista == NULL) {
        tabela[indice].lista = novo;
    } else {
        Node *atual = tabela[indice].lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }

    printf("Chave %d inserida na posicao %d com encadeamento separado.\n", chave, indice);
}

// Função para buscar uma chave na tabela hash usando encadeamento separado
int busca(TabelaHash tabela[], int chave, int *passos, int *colisoes, double *tempo_busca) {
    unsigned int indice = hash1(chave);
    *passos = 0;
    *colisoes = 0;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    Node *atual = tabela[indice].lista;
    while (atual != NULL) {
        (*passos)++;
        if (atual->chave == chave) {
            clock_gettime(CLOCK_MONOTONIC, &end);
            *tempo_busca = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
            return indice;
        }
        (*colisoes)++;
        atual = atual->prox;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    *tempo_busca = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    return -1; // Chave não encontrada
}

// Função para ler os arquivos e carregar os dados na tabela hash
void carregaArquivo(const char* nomeArquivo, TabelaHash tabela[]) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        exit(1);
    }

    int chave;
    while (fscanf(arquivo, "%d", &chave) != EOF) {
        insere(tabela, chave);
    }

    fclose(arquivo);
    printf("\n\nTabela carregada.\n\n");
}

// Função principal
int main() {
    TabelaHash tabela[TABLE_SIZE];
    inicializaTabela(tabela);

    // Carrega o arquivo "numeros_aleatorios.txt" na tabela hash
    carregaArquivo("numeros_aleatorios.txt", tabela);

    // Desabilita mensagens de debug após carregar a tabela
    printf("\nInsercao de chaves concluida.\n");

    // Abrir o arquivo "checkin.txt" para buscar as chaves
    FILE *arquivoCheckin = fopen("checkin.txt", "r");
    if (arquivoCheckin == NULL) {
        printf("Erro ao abrir o arquivo checkin.txt\n");
        return 1;
    }

    int chave;
    int passos, colisoes;
    double tempo_busca;

    while (fscanf(arquivoCheckin, "%d", &chave) != EOF) {
        int indice = busca(tabela, chave, &passos, &colisoes, &tempo_busca);

        if (indice != -1) {
            printf("Chave %d encontrada na posicao %d com %d passos e %d colisoes. Tempo: %.9f segundos\n",
                   chave, indice, passos, colisoes, tempo_busca);
        } else {
            printf("Chave %d nao encontrada.\n", chave);
        }
    }

    fclose(arquivoCheckin);

    return 0;
}

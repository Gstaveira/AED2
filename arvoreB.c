#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CHAVES 4 //
#define MIN_CHAVES 2 //

//struct arvore B
typedef struct NoArvoreB {
    int chaves[MAX_CHAVES];
    struct NoArvoreB *filhos[5];
    int quantidade_chaves;
    bool eh_folha;
} NoArvoreB;

// criar um novo nó de árvore B
NoArvoreB *criarNovoNo(bool ehFolha) {
    NoArvoreB *novoNo = (NoArvoreB *)malloc(sizeof(NoArvoreB));
    if (novoNo == NULL) {
        return NULL;
    }
    novoNo->eh_folha = ehFolha;
    novoNo->quantidade_chaves = 0;
    for (int i = 0; i <= MAX_CHAVES; i++) {
        novoNo->filhos[i] = NULL;
    }
    return novoNo;
}

//buscar chave na árvore B
NoArvoreB *buscarChave(NoArvoreB *raiz, int chave) {
    int indice = 0;

    while (indice < raiz->quantidade_chaves && chave > raiz->chaves[indice]) {
        indice++;
    }

    if (indice < raiz->quantidade_chaves && raiz->chaves[indice] == chave) {
        return raiz;
    }

    if (raiz->eh_folha) {
        return NULL;
    }

    return buscarChave(raiz->filhos[indice], chave);
}

//dividir um nó cheio
void dividirNo(NoArvoreB *noPai, int indice, NoArvoreB *noCheio) {

    NoArvoreB *novoFilho = criarNovoNo(noCheio->eh_folha);
    novoFilho->quantidade_chaves = MIN_CHAVES;

    for (int j = 0; j < MIN_CHAVES; j++) {
        novoFilho->chaves[j] = noCheio->chaves[j + MIN_CHAVES + 1];
    }
    if (!noCheio->eh_folha) {
        for (int j = 0; j <= MIN_CHAVES; j++) {
            novoFilho->filhos[j] = noCheio->filhos[j + MIN_CHAVES + 1];
        }
    }

    noCheio->quantidade_chaves = MIN_CHAVES;

    for (int j = noPai->quantidade_chaves; j >= indice + 1; j--) {
        noPai->filhos[j + 1] = noPai->filhos[j];
    }

    noPai->filhos[indice + 1] = novoFilho;

    for (int j = noPai->quantidade_chaves - 1; j >= indice; j--) {
        noPai->chaves[j + 1] = noPai->chaves[j];
    }

    noPai->chaves[indice] = noCheio->chaves[MIN_CHAVES];
    noPai->quantidade_chaves++;
}

//inserir chave na árvore B
void inserirEmNoNaoCheio(NoArvoreB *raiz, int chave) {
    int indice = raiz->quantidade_chaves - 1;

    if (raiz->eh_folha) {
        while (indice >= 0 && chave < raiz->chaves[indice]) {
            raiz->chaves[indice + 1] = raiz->chaves[indice];
            indice--;
        }
        raiz->chaves[indice + 1] = chave;
        raiz->quantidade_chaves++;
    } else {

        while (indice >= 0 && chave < raiz->chaves[indice]) {
            indice--;
        }
        indice++;

        if (raiz->filhos[indice]->quantidade_chaves == MAX_CHAVES) {
            dividirNo(raiz, indice, raiz->filhos[indice]);

            if (chave > raiz->chaves[indice]) {
                indice++;
            }
        }
        inserirEmNoNaoCheio(raiz->filhos[indice], chave);
    }
}

//inserir chave na árvore B
void inserirChave(NoArvoreB **raiz, int chave) {
    NoArvoreB *raizAtual = *raiz;
    // Se a raiz está cheia, criar uma nova raiz
    if (raizAtual->quantidade_chaves == MAX_CHAVES) {
        NoArvoreB *novaRaiz = criarNovoNo(false);
        novaRaiz->filhos[0] = raizAtual;
        dividirNo(novaRaiz, 0, raizAtual);
        // Inserir a chave na nova raiz
        inserirEmNoNaoCheio(novaRaiz, chave);
        *raiz = novaRaiz;
    } else {
        inserirEmNoNaoCheio(raizAtual, chave);
    }
}

//imprimir árvore B
void imprimirArvoreB(NoArvoreB *raiz, int nivel) {
    if (raiz != NULL) {
        for (int i = 0; i < nivel; i++) {
            printf("  ");
        }
        printf("| ");
        for (int i = 0; i < raiz->quantidade_chaves; i++) {
            printf("%d ", raiz->chaves[i]);
        }
        printf("\n");
        if (!raiz->eh_folha) {
            for (int i = 0; i <= raiz->quantidade_chaves; i++) {
                imprimirArvoreB(raiz->filhos[i], nivel + 1);
            }
        }
    }
}


int main() {
    // Criar uma árvore B com raiz como folha
    NoArvoreB *raiz = criarNovoNo(true);

    int chaves[] = {20, 10, 30, 5, 15, 25, 35, 40};
    for (int i = 0; i < 8; i++) {
        inserirChave(&raiz, chaves[i]);
    }

    // Imprimir a árvore B
    printf("Arvore B:\n");
    imprimirArvoreB(raiz, 0);

    // Busca uma chave na árvore B
    int chaveBuscar = 15;
    NoArvoreB *resultado = buscarChave(raiz, chaveBuscar);
    if (resultado != NULL) {
        printf("\nChave %d encontrada na arvore B.\n", chaveBuscar);
    } else {
        printf("\nChave %d não encontrada na arvore B.\n", chaveBuscar);
    }


    return 0;
}

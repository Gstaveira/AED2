#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 256 // Quantidade m�xima de caracteres (ASCII)

// Estrutura para representar um n� na �rvore de Huffman
typedef struct No {
    char caractere; // Caractere ou '\0' para n� interno
    unsigned int frequencia; // Frequ�ncia
    struct No *esquerdo, *direito; // Filhos
} No;

// Estrutura para armazenar a frequ�ncia de cada caractere
typedef struct Frequencia {
    char caractere;
    unsigned int frequencia;
} Frequencia;

// Fun��o para criar um novo n� de �rvore de Huffman
No* criarNo(char caractere, unsigned int frequencia) {
    No* no = (No*)malloc(sizeof(No));
    no->caractere = caractere;
    no->frequencia = frequencia;
    no->esquerdo = NULL;
    no->direito = NULL;
    return no;
}

// Fun��o para comparar dois n�s com base na frequ�ncia (usada para ordenar)
int compararNos(const void* a, const void* b) {
    No* noA = *(No**)a;
    No* noB = *(No**)b;
    return noA->frequencia - noB->frequencia;
}

// Fun��o para construir a �rvore de Huffman com base nas frequ�ncias
No* construirArvoreHuffman(Frequencia* frequencias, int tamanho) {
    // Array de n�s
    No** nos = (No**)malloc(tamanho * sizeof(No*));
    for (int i = 0; i < tamanho; i++) {
        nos[i] = criarNo(frequencias[i].caractere, frequencias[i].frequencia);
    }

    // Ordenar os n�s pela frequ�ncia
    qsort(nos, tamanho, sizeof(No*), compararNos);

    // Constru��o da �rvore de Huffman
    while (tamanho > 1) {
        // Combinar os dois n�s de menor frequ�ncia
        No* esquerdo = nos[0];
        No* direito = nos[1];

        // Criar um novo n� interno com a soma das frequ�ncias
        No* novoNo = criarNo('\0', esquerdo->frequencia + direito->frequencia);
        novoNo->esquerdo = esquerdo;
        novoNo->direito = direito;

        // Remover os dois n�s combinados e adicionar o novo n�
        memmove(&nos[0], &nos[2], (tamanho - 2) * sizeof(No*));
        nos[0] = novoNo;
        tamanho--;

        // Ordenar novamente
        qsort(nos, tamanho, sizeof(No*), compararNos);
    }

    // O �ltimo n� restante � a raiz da �rvore de Huffman
    No* raiz = nos[0];
    free(nos);
    return raiz;
}

// Fun��o para imprimir os c�digos de Huffman
void imprimirCodigosHuffman(No* raiz, char* codigo, int comprimento) {
    if (!raiz) {
        return;
    }

    // Se o n� for uma folha, imprimir a codifica��o
    if (!raiz->esquerdo && !raiz->direito) {
        codigo[comprimento] = '\0';
        printf("%c: %s\n", raiz->caractere, codigo);
        return;
    }

    // Adicionar 0 para o filho � esquerda
    codigo[comprimento] = '0';
    imprimirCodigosHuffman(raiz->esquerdo, codigo, comprimento + 1);

    // Adicionar 1 para o filho � direita
    codigo[comprimento] = '1';
    imprimirCodigosHuffman(raiz->direito, codigo, comprimento + 1);
}

int main() {
    // Exemplo de lista de frequ�ncias de caracteres
    Frequencia frequencias[] = {
        {'a', 5},
        {'b', 9},
        {'c', 12},
        {'d', 13},
        {'e', 16},
        {'f', 45}
    };
    int tamanho = sizeof(frequencias) / sizeof(frequencias[0]);

    // Construir a �rvore de Huffman com base nas frequ�ncias fornecidas
    printf("Construindo a arvore de Huffman com base nas frequencias fornecidas...\n");
    No* raiz = construirArvoreHuffman(frequencias, tamanho);

    // Imprimir os c�digos de Huffman para cada caractere
    printf("\nCodigos de Huffman para cada caractere:\n");
    char codigo[MAX_CHAR]; // Array para armazenar a codifica��o tempor�ria
    imprimirCodigosHuffman(raiz, codigo, 0);

    // Liberar mem�ria da �rvore de Huffman
    // Voc� deve adicionar uma fun��o para liberar a mem�ria da �rvore
    // Por exemplo: liberarArvore(raiz);
    printf("\nFinalizando o programa...\n");

    return 0;
}

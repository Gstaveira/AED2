#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 256 // Quantidade máxima de caracteres (ASCII)

// Estrutura para representar um nó na árvore de Huffman
typedef struct No {
    char caractere; // Caractere ou '\0' para nó interno
    unsigned int frequencia; // Frequência
    struct No *esquerdo, *direito; // Filhos
} No;

// Estrutura para armazenar a frequência de cada caractere
typedef struct Frequencia {
    char caractere;
    unsigned int frequencia;
} Frequencia;

// Função para criar um novo nó de árvore de Huffman
No* criarNo(char caractere, unsigned int frequencia) {
    No* no = (No*)malloc(sizeof(No));
    no->caractere = caractere;
    no->frequencia = frequencia;
    no->esquerdo = NULL;
    no->direito = NULL;
    return no;
}

// Função para comparar dois nós com base na frequência (usada para ordenar)
int compararNos(const void* a, const void* b) {
    No* noA = *(No**)a;
    No* noB = *(No**)b;
    return noA->frequencia - noB->frequencia;
}

// Função para construir a árvore de Huffman com base nas frequências
No* construirArvoreHuffman(Frequencia* frequencias, int tamanho) {
    // Array de nós
    No** nos = (No**)malloc(tamanho * sizeof(No*));
    for (int i = 0; i < tamanho; i++) {
        nos[i] = criarNo(frequencias[i].caractere, frequencias[i].frequencia);
    }

    // Ordenar os nós pela frequência
    qsort(nos, tamanho, sizeof(No*), compararNos);

    // Construção da árvore de Huffman
    while (tamanho > 1) {
        // Combinar os dois nós de menor frequência
        No* esquerdo = nos[0];
        No* direito = nos[1];

        // Criar um novo nó interno com a soma das frequências
        No* novoNo = criarNo('\0', esquerdo->frequencia + direito->frequencia);
        novoNo->esquerdo = esquerdo;
        novoNo->direito = direito;

        // Remover os dois nós combinados e adicionar o novo nó
        memmove(&nos[0], &nos[2], (tamanho - 2) * sizeof(No*));
        nos[0] = novoNo;
        tamanho--;

        // Ordenar novamente
        qsort(nos, tamanho, sizeof(No*), compararNos);
    }

    // O último nó restante é a raiz da árvore de Huffman
    No* raiz = nos[0];
    free(nos);
    return raiz;
}

// Função para imprimir os códigos de Huffman
void imprimirCodigosHuffman(No* raiz, char* codigo, int comprimento) {
    if (!raiz) {
        return;
    }

    // Se o nó for uma folha, imprimir a codificação
    if (!raiz->esquerdo && !raiz->direito) {
        codigo[comprimento] = '\0';
        printf("%c: %s\n", raiz->caractere, codigo);
        return;
    }

    // Adicionar 0 para o filho à esquerda
    codigo[comprimento] = '0';
    imprimirCodigosHuffman(raiz->esquerdo, codigo, comprimento + 1);

    // Adicionar 1 para o filho à direita
    codigo[comprimento] = '1';
    imprimirCodigosHuffman(raiz->direito, codigo, comprimento + 1);
}

int main() {
    // Exemplo de lista de frequências de caracteres
    Frequencia frequencias[] = {
        {'a', 5},
        {'b', 9},
        {'c', 12},
        {'d', 13},
        {'e', 16},
        {'f', 45}
    };
    int tamanho = sizeof(frequencias) / sizeof(frequencias[0]);

    // Construir a árvore de Huffman com base nas frequências fornecidas
    printf("Construindo a arvore de Huffman com base nas frequencias fornecidas...\n");
    No* raiz = construirArvoreHuffman(frequencias, tamanho);

    // Imprimir os códigos de Huffman para cada caractere
    printf("\nCodigos de Huffman para cada caractere:\n");
    char codigo[MAX_CHAR]; // Array para armazenar a codificação temporária
    imprimirCodigosHuffman(raiz, codigo, 0);

    // Liberar memória da árvore de Huffman
    // Você deve adicionar uma função para liberar a memória da árvore
    // Por exemplo: liberarArvore(raiz);
    printf("\nFinalizando o programa...\n");

    return 0;
}

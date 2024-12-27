#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcoes.h"



// Cria e inicializa um heap com tamanho máximo
Heap* criarHeap(int tamanhoMaximo) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->arrayHeap = (Pedido*)malloc(tamanhoMaximo * sizeof(Pedido));
    heap->tamanhoMaximo = tamanhoMaximo;
    heap->tamanhoAtual = 0;
    return heap;
}

// Libera a memória alocada para o heap
void destruirHeap(Heap* heap) {
    free(heap->arrayHeap);
    free(heap);
}

// Insere um pedido no heap
void inserirPedido(Heap* heap, Pedido pedido) {
    if (heap->tamanhoAtual == heap->tamanhoMaximo) {
        printf("Heap está cheio. Nao e possível inserir mais pedidos.\n");
        return;
    }
    heap->arrayHeap[heap->tamanhoAtual] = pedido;
    heapifyUp(heap, heap->tamanhoAtual);
    heap->tamanhoAtual++;
}

// Remove e retorna o pedido de maior prioridade do heap
Pedido removerPedidoMaiorPrioridade(Heap* heap) {
    if (heap->tamanhoAtual == 0) {
        printf("Heap está vazio. Nao e possível remover pedidos.\n");
        Pedido pedidoVazio;
        pedidoVazio.idPedido = -1;
        return pedidoVazio;
    }
    Pedido pedidoMaiorPrioridade = heap->arrayHeap[0];
    heap->arrayHeap[0] = heap->arrayHeap[heap->tamanhoAtual - 1];
    heap->tamanhoAtual--;
    heapifyDown(heap, 0);
    return pedidoMaiorPrioridade;
}

// Busca um pedido pelo ID no heap
Pedido* buscarPedido(Heap* heap, int idPedido) {
    for (int i = 0; i < heap->tamanhoAtual; i++) {
        if (heap->arrayHeap[i].idPedido == idPedido) {
            return &heap->arrayHeap[i];
        }
    }
    return NULL;
}

// Imprime todos os pedidos no heap
void imprimirPedidos(Heap* heap) {
    for (int i = 0; i < heap->tamanhoAtual; i++) {
        printf("Pedido ID: %d, Cliente: %s, Descricao: %s, Prioridade: %d\n",
            heap->arrayHeap[i].idPedido,
            heap->arrayHeap[i].nomeCliente,
            heap->arrayHeap[i].descricaoPedido,
            heap->arrayHeap[i].prioridade);
    }
}


// Altera a prioridade de um pedido específico
void alterarPrioridadePedido(Heap* heap, int idPedido, int novaPrioridade) {
    for (int i = 0; i < heap->tamanhoAtual; i++) {
        if (heap->arrayHeap[i].idPedido == idPedido) {
            heap->arrayHeap[i].prioridade = novaPrioridade;
            heapifyUp(heap, i);
            heapifyDown(heap, i);
            return;
        }
    }
}

// Atualiza as informações de um pedido
void atualizarPedido(Heap* heap, Pedido pedidoAtualizado) {
    for (int i = 0; i < heap->tamanhoAtual; i++) {
        if (heap->arrayHeap[i].idPedido == pedidoAtualizado.idPedido) {
            heap->arrayHeap[i] = pedidoAtualizado;
            heapifyUp(heap, i);
            heapifyDown(heap, i);
            return;
        }
    }
}

// Verifica a integridade do heap
bool verificarIntegridadeHeap(Heap* heap) {
    for (int i = 0; i < heap->tamanhoAtual; i++) {
        int indiceFilhoEsquerdo = obterIndiceFilhoEsquerdo(i);
        int indiceFilhoDireito = obterIndiceFilhoDireito(i);
        if (indiceFilhoEsquerdo < heap->tamanhoAtual && heap->arrayHeap[indiceFilhoEsquerdo].prioridade > heap->arrayHeap[i].prioridade) {
            return false;
        }
        if (indiceFilhoDireito < heap->tamanhoAtual && heap->arrayHeap[indiceFilhoDireito].prioridade > heap->arrayHeap[i].prioridade) {
            return false;
        }
    }
    return true;
}


// Ajusta o heap após uma inserção
void heapifyUp(Heap* heap, int indice) {
    int indicePai = obterIndicePai(indice);
    while (indice > 0 && heap->arrayHeap[indice].prioridade > heap->arrayHeap[indicePai].prioridade) {
        trocarPedidos(&heap->arrayHeap[indice], &heap->arrayHeap[indicePai]);
        indice = indicePai;
        indicePai = obterIndicePai(indice);
    }
}

// Ajusta o heap após uma remoção
void heapifyDown(Heap* heap, int indice) {
    int indiceFilhoEsquerdo = obterIndiceFilhoEsquerdo(indice);
    int indiceFilhoDireito = obterIndiceFilhoDireito(indice);
    int maior = indice;

    if (indiceFilhoEsquerdo < heap->tamanhoAtual && heap->arrayHeap[indiceFilhoEsquerdo].prioridade > heap->arrayHeap[maior].prioridade) {
        maior = indiceFilhoEsquerdo;
    }
    if (indiceFilhoDireito < heap->tamanhoAtual && heap->arrayHeap[indiceFilhoDireito].prioridade > heap->arrayHeap[maior].prioridade) {
        maior = indiceFilhoDireito;
    }
    if (maior != indice) {
        trocarPedidos(&heap->arrayHeap[indice], &heap->arrayHeap[maior]);
        heapifyDown(heap, maior);
    }
}

// Retorna o índice do filho esquerdo
int obterIndiceFilhoEsquerdo(int indicePai) {
    return 2 * indicePai + 1;
}

// Retorna o índice do filho direito
int obterIndiceFilhoDireito(int indicePai) {
    return 2 * indicePai + 2;
}

// Retorna o índice do pai
int obterIndicePai(int indiceFilho) {
    return (indiceFilho - 1) / 2;
}

// Troca dois pedidos de lugar
void trocarPedidos(Pedido* a, Pedido* b) {
    Pedido temp = *a;
    *a = *b;
    *b = temp;
}

// Verifica se a prioridade é válida (deve ser um número positivo)
int validarPrioridade(int prioridade) {
    return prioridade > 0;
}

// Verifica se o ID é válido (deve ser um número positivo)
int validarID(int id) {
    return id > 0;
}

// Verifica se o nome é válido (não vazio e apenas letras)
int validarNome(const char* nome) {
    if (strlen(nome) == 0) return 0;
    for (int i = 0; nome[i] != '\0'; i++) {
        if (!isalpha(nome[i])) return 0;
    }
    return 1;
}

// Verifica se a descrição é válida (não vazia)
int validarDescricao(const char* descricao) {
    return strlen(descricao) > 0;
}


// Exibe o menu de opções
void mostrarMenu() {
    printf("1. Inserir pedido\n");
    printf("2. Remover pedido de maior prioridade\n");
    printf("3. Buscar pedido\n");
    printf("4. Listar pedidos\n");
    printf("5. Alterar prioridade de um pedido\n");
    printf("6. Atualizar informacoes de um pedido\n");
    printf("7. Verificar integridade do heap\n");
    printf("8. Sair\n");
}

// Lida com a escolha do usuário
void lidarComEscolhaUsuario(Heap* heap) {
    int escolha;
    int idPedido, novaPrioridade;
    char nomeCliente[100], descricaoPedido[256];
    Pedido pedido, *pedidoBuscado;

    while (1) {
        mostrarMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                printf("Inserir pedido:\n");
                printf("ID do pedido: ");
                scanf("%d", &idPedido);
                while (!validarID(idPedido)) {
                    printf("ID inválido, digite novamente: ");
                    scanf("%d", &idPedido);
                }
                printf("Nome do cliente: ");
                scanf("%s", nomeCliente);
                while (!validarNome(nomeCliente)) {
                    printf("Nome invalido, digite novamente: ");
                    scanf("%s", nomeCliente);
                }
                printf("Descricao do pedido: ");
                scanf(" %[^\n]", descricaoPedido);
                while (!validarDescricao(descricaoPedido)) {
                    printf("Descrição invalida, digite novamente: ");
                    scanf(" %[^\n]", descricaoPedido);
                }
                printf("Prioridade do pedido: ");
                scanf("%d", &pedido.prioridade);
                while (!validarPrioridade(pedido.prioridade)) {
                    printf("Prioridade invalida, digite novamente: ");
                    scanf("%d", &pedido.prioridade);
                }
                pedido.idPedido = idPedido;
                strcpy(pedido.nomeCliente, nomeCliente);
                strcpy(pedido.descricaoPedido, descricaoPedido);
                inserirPedido(heap, pedido);
                break;
            case 2:
                pedido = removerPedidoMaiorPrioridade(heap);
                if (pedido.idPedido != -1) {
                    printf("Pedido removido: ID: %d, Cliente: %s, Descricao: %s, Prioridade: %d\n",
                        pedido.idPedido, pedido.nomeCliente, pedido.descricaoPedido, pedido.prioridade);
                }
                break;
            case 3:
                printf("Buscar pedido:\n");
                printf("ID do pedido: ");
                scanf("%d", &idPedido);
                pedidoBuscado = buscarPedido(heap, idPedido);
                if (pedidoBuscado) {
                    printf("Pedido encontrado: ID: %d, Cliente: %s, Descricao: %s, Prioridade: %d\n",
                        pedidoBuscado->idPedido, pedidoBuscado->nomeCliente, pedidoBuscado->descricaoPedido, pedidoBuscado->prioridade);
                } else {
                    printf("Pedido nao encontrado.\n");
                }
                break;
            case 4:
                imprimirPedidos(heap);
                break;
            case 5:
                printf("Alterar prioridade do pedido:\n");
                printf("ID do pedido: ");
                scanf("%d", &idPedido);
                printf("Nova prioridade: ");
                scanf("%d", &novaPrioridade);
                while (!validarPrioridade(novaPrioridade)) {
                    printf("Prioridade invalida, digite novamente: ");
                    scanf("%d", &novaPrioridade);
                }
                alterarPrioridadePedido(heap, idPedido, novaPrioridade);
                break;
            case 6:
                printf("Atualizar pedido:\n");
                printf("ID do pedido: ");
                scanf("%d", &idPedido);
                while (!validarID(idPedido)) {
                    printf("ID inválido, digite novamente: ");
                    scanf("%d", &idPedido);
                }
                printf("Nome do cliente: ");
                scanf("%s", nomeCliente);
                while (!validarNome(nomeCliente)) {
                    printf("Nome invalido, digite novamente: ");
                    scanf("%s", nomeCliente);
                }
                printf("Descricao do pedido: ");
                scanf(" %[^\n]", descricaoPedido);
                while (!validarDescricao(descricaoPedido)) {
                    printf("Descrição inválida, digite novamente: ");
                    scanf(" %[^\n]", descricaoPedido);
                }
                printf("Prioridade do pedido: ");
                scanf("%d", &pedido.prioridade);
                while (!validarPrioridade(pedido.prioridade)) {
                    printf("Prioridade invalida, digite novamente: ");
                    scanf("%d", &pedido.prioridade);
                }
                pedido.idPedido = idPedido;
                strcpy(pedido.nomeCliente, nomeCliente);
                strcpy(pedido.descricaoPedido, descricaoPedido);
                atualizarPedido(heap, pedido);
                break;
            case 7:
                if (verificarIntegridadeHeap(heap)) {
                    printf("A integridade do heap esta correta.\n");
                } else {
                    printf("A integridade do heap esta comprometida.\n");
                }
                break;
            case 8:
                return;
            default:
                printf("Opcao invalida.\n");
        }
    }
}


int main() {
    int tamanhoMaximo;
    printf("Digite o tamanho maximo do heap: ");
    scanf("%d", &tamanhoMaximo);

    Heap* heap = criarHeap(tamanhoMaximo);

    lidarComEscolhaUsuario(heap);

    destruirHeap(heap);

    return 0;
}


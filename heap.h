#include <stdbool.h>

// Estrutura para armazenar os dados de um pedido
typedef struct {
    int idPedido;
    char nomeCliente[100];
    char descricaoPedido[256];
    int prioridade; // Maior valor significa maior prioridade
} Pedido;

// Estrutura para gerenciar o heap de pedidos
typedef struct {
    Pedido* arrayHeap;
    int tamanhoMaximo;
    int tamanhoAtual;
} Heap;

// Funções de Manipulação do Heap
Heap* criarHeap(int tamanhoMaximo); // Cria e inicializa um heap com tamanho máximo
void destruirHeap(Heap* heap); // Libera a memória alocada para o heap
void inserirPedido(Heap* heap, Pedido pedido); // Insere um pedido no heap
Pedido removerPedidoMaiorPrioridade(Heap* heap); // Remove e retorna o pedido de maior prioridade do heap
Pedido* buscarPedido(Heap* heap, int idPedido); // Busca um pedido pelo ID no heap
void imprimirPedidos(Heap* heap); // Imprime todos os pedidos no heap
void alterarPrioridadePedido(Heap* heap, int idPedido, int novaPrioridade); // Altera a prioridade de um pedido específico
void atualizarPedido(Heap* heap, Pedido pedidoAtualizado); // Atualiza as informações de um pedido
bool verificarIntegridadeHeap(Heap* heap); // Verifica a integridade do heap

// Funções Auxiliares
void heapifyUp(Heap* heap, int indice); // Ajusta o heap após uma inserção
void heapifyDown(Heap* heap, int indice); // Ajusta o heap após uma remoção
int obterIndiceFilhoEsquerdo(int indicePai); // Retorna o índice do filho esquerdo
int obterIndiceFilhoDireito(int indicePai); // Retorna o índice do filho direito
int obterIndicePai(int indiceFilho); // Retorna o índice do pai
void trocarPedidos(Pedido* a, Pedido* b); // Troca dois pedidos de lugar
int validarPrioridade(int prioridade); // Verifica se a prioridade é válida
int validarID(int id); // Verifica se o ID é válido
int validarNome(const char* nome); // Verifica se o nome é válido
int validarDescricao(const char* descricao); // Verifica se a descrição é válida

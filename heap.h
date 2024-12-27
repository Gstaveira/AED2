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

// Fun��es de Manipula��o do Heap
Heap* criarHeap(int tamanhoMaximo); // Cria e inicializa um heap com tamanho m�ximo
void destruirHeap(Heap* heap); // Libera a mem�ria alocada para o heap
void inserirPedido(Heap* heap, Pedido pedido); // Insere um pedido no heap
Pedido removerPedidoMaiorPrioridade(Heap* heap); // Remove e retorna o pedido de maior prioridade do heap
Pedido* buscarPedido(Heap* heap, int idPedido); // Busca um pedido pelo ID no heap
void imprimirPedidos(Heap* heap); // Imprime todos os pedidos no heap
void alterarPrioridadePedido(Heap* heap, int idPedido, int novaPrioridade); // Altera a prioridade de um pedido espec�fico
void atualizarPedido(Heap* heap, Pedido pedidoAtualizado); // Atualiza as informa��es de um pedido
bool verificarIntegridadeHeap(Heap* heap); // Verifica a integridade do heap

// Fun��es Auxiliares
void heapifyUp(Heap* heap, int indice); // Ajusta o heap ap�s uma inser��o
void heapifyDown(Heap* heap, int indice); // Ajusta o heap ap�s uma remo��o
int obterIndiceFilhoEsquerdo(int indicePai); // Retorna o �ndice do filho esquerdo
int obterIndiceFilhoDireito(int indicePai); // Retorna o �ndice do filho direito
int obterIndicePai(int indiceFilho); // Retorna o �ndice do pai
void trocarPedidos(Pedido* a, Pedido* b); // Troca dois pedidos de lugar
int validarPrioridade(int prioridade); // Verifica se a prioridade � v�lida
int validarID(int id); // Verifica se o ID � v�lido
int validarNome(const char* nome); // Verifica se o nome � v�lido
int validarDescricao(const char* descricao); // Verifica se a descri��o � v�lida

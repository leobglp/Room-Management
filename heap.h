#ifndef HEAP_H
#define HEAP_H

/**
 * @brief Struct para o Heap Maximo
 * @typedef MaxHeap
*/
typedef struct max_heap MaxHeap;

/**
 * @brief Cria o heap
 * @param capacidade
 * @return MaxHeap
*/
MaxHeap *criarHeap(int capacidade);

/**
 * @brief Troca as posicoes dentro do heap
 * @param v1, v2
 * @return void
*/
void troca(int *v1, int *v2);

/**
 * @brief Realiza o heapify(organizacao do heap)
 * @param heap, i
 * @return void
*/
void heapify(MaxHeap* heap, int i);

/**
 * @brief Insere uma nova reserva no heap
 * @param heap, sala, chave
 * @return void
*/
void inserirHeap(MaxHeap* heap, Sala *sala, int chave);

/**
 * @brief Atualzia da prioridade de uma reserva
 * @param heap, codigo, int
 * @return void
*/
void atualizarPrioridade(MaxHeap* heap, int codigo, int novaPrioridade);

/**
 * @brief Cancela uma reserva do heap
 * @param heap, codigo
 * @return void
*/
void cancelarHeap(MaxHeap* heap, int codigo);

/**
 * @brief Desaloca o heap
 * @param heap
 * @return void
*/
void desalocarHeap(MaxHeap* heap);

/**
 * @brief Escreve no arquivo de saida a lista de reservas
 * @param heap, arq
 * @return void
*/
void escreverHeap(MaxHeap* heap, FILE *arq);

#endif
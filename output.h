#ifndef OUTPUT_H
#define OUTPUT_H

/**
 * @brief Escreve no arquivo de saída
 * @param opcao, codigo, prioridade, capacidade, estado, raiz, heap
 * @return void
*/
void outputLog(char *opcao, int codigo, int prioridade, int capacidade, char *estado, No *raiz, MaxHeap *heap);

#endif
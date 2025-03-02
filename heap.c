#include "libraries.h"

typedef struct max_heap{
    int *vetor;
    int capacidade;
    Sala **salas;
}MaxHeap;

MaxHeap *criarHeap(int capacidade){
    MaxHeap *heap=(MaxHeap*)malloc(sizeof(MaxHeap));
    heap->vetor = (int*) malloc((capacidade + 1) * sizeof(int));
    heap->salas=(Sala**)malloc((capacidade+1)*sizeof(Sala*));
    heap->vetor[0] = 0;
    heap->capacidade = capacidade;
    return heap;
}

void troca(int *v1, int *v2) {
    int aux=*v1;
    *v1=*v2;
    *v2=aux;
}

void heapify(MaxHeap* heap, int i) {
    int maior = i;
    int filhoEsquerda = 2 * i;
    int filhoDireita = 2 * i + 1;

    if(filhoEsquerda<=heap->vetor[0] && heap->vetor[filhoEsquerda]>heap->vetor[maior]){
        maior = filhoEsquerda;
    }
    if(filhoDireita<=heap->vetor[0] && heap->vetor[filhoDireita]>heap->vetor[maior]){
        maior = filhoDireita;
    }
    if(maior != i){
        troca(&heap->vetor[i], &heap->vetor[maior]);
        heapify(heap, maior);
    }
}

void inserirHeap(MaxHeap* heap, Sala *sala, int chave) {
    if(heap->vetor[0] == heap->capacidade){
        int* vet = realloc(heap->vetor, (heap->capacidade * 2 + 1) * sizeof(int));
        Sala** novaSala=realloc(heap->salas, (heap->capacidade*2+1)*sizeof(Sala*));
        if(vet!=NULL && novaSala!=NULL){
            heap->vetor = vet;
            heap->salas=novaSala;
            heap->capacidade *= 2;
        } else {
            printf("Erro ao realocar memoria\n");
            return;
        }
    }
    heap->vetor[0]++;
    int i = heap->vetor[0];
    heap->vetor[i] = chave;
    heap->salas[i]=sala;
    while(i>1 && heap->vetor[i]>heap->vetor[i / 2]){
        troca(&heap->vetor[i], &heap->vetor[i / 2]);
        Sala *aux=heap->salas[i];
        heap->salas[i]=heap->salas[i/2];
        heap->salas[i/2]=aux;
        i /= 2;
    }
}

void atualizarPrioridade(MaxHeap* heap, int codigo, int novaPrioridade){
    int indice = -1;

    for(int i=1; i <= heap->vetor[0]; i++){
        if (heap->salas[i]->codigo == codigo) {
            indice = i;
            break;
        }
    }

    if(indice == -1){
        printf("Reserva %d nao encontrada\n", codigo);
        return;
    }

    int prioridadeAntiga = heap->vetor[indice];
    heap->vetor[indice] = novaPrioridade;

    if(novaPrioridade > prioridadeAntiga){
        while (indice>1 && heap->vetor[indice]>heap->vetor[indice / 2]) {
            troca(&heap->vetor[indice], &heap->vetor[indice / 2]);
            Sala *aux = heap->salas[indice];
            heap->salas[indice] = heap->salas[indice / 2];
            heap->salas[indice / 2] = aux;
            indice /= 2;
        }
    }

    else if(novaPrioridade < prioridadeAntiga) {
        heapify(heap, indice);
    }
}

void cancelarHeap(MaxHeap* heap, int codigo) {
    int indice = -1;

    for(int i=1; i<=heap->vetor[0]; i++){
        if(heap->salas[i]->codigo == codigo){
            indice = i;
            break;
        }
    }
    if(indice == -1){
        printf("Reserva %d nao encontrada\n", codigo);
    }
    heap->vetor[indice]=heap->vetor[heap->vetor[0]];
    heap->salas[indice]=heap->salas[heap->vetor[0]];
    heap->vetor[0]--;
    heapify(heap, indice);
}

void desalocarHeap(MaxHeap* heap) {
    if(heap){
        free(heap->vetor);
        free(heap->salas);
        free(heap);
    }
}

void escreverHeap(MaxHeap* heap, FILE *arq){
    if(heap->vetor[0] == 0){
        fprintf(arq, "Heap vazio!\n");
        return;
    }
    for(int i=1; i <= heap->vetor[0]; i++){
        fprintf(arq, "\tSala: %d Prioridade: %d\n", heap->salas[i]->codigo, heap->vetor[i]);
    }
}
#include "libraries.h"

#define FC_MAX 0.7

typedef struct no_hash{
    Sala *sala;
    struct no_hash *prox;
}NoHash;

typedef struct lista{
    NoHash *inicio;
    int tam;
}Lista;

void iniciaLista(Lista *lista){
    lista->inicio=NULL;
    lista->tam=0;
}

void insereLista(Lista *lista, Sala *sala){
    NoHash *novo=(NoHash*)malloc(sizeof(NoHash));
    if(novo){
        novo->sala=sala;
        novo->prox=lista->inicio;
        lista->inicio=novo;
        lista->tam++;
    }else{
        printf("\nErro ao alocar memoria na insercao na lista");
    }
}

char *buscarLista(Lista *lista, int chave){
    NoHash *aux=lista->inicio;
    while(aux && aux->sala->codigo != chave){
        aux=aux->prox;
    }
    if(aux){
        return aux->sala->estado;
    }
    return NULL;
}

void iniciaTabela(TabelaHash *tabelaHash, int capacidade){
    tabelaHash->capacidade=capacidade;
    tabelaHash->itens=0;
    tabelaHash->tabela=(Lista*)malloc(capacidade*sizeof(Lista));

    if(!tabelaHash->tabela){
        printf("\nErro ao alocar tabela hash");
    }

    for(int i=0; i<capacidade; i++){
        iniciaLista(&tabelaHash->tabela[i]);
    }
}

int hash(int chave, int capacidade){
    return chave % capacidade;
}

void redimensionar(TabelaHash *tabelaHash){
    int novaCapacidade=tabelaHash->capacidade*2;
    int i;
    Lista *novaTabela=(Lista*)malloc(novaCapacidade*sizeof(Lista));

    if(!novaTabela){
        printf("\nErro ao alocar redimensionamento");
    }

    for(i=0; i<novaCapacidade; i++){
        iniciaLista(&novaTabela[i]);
    }

    for(i=0; i<tabelaHash->capacidade; i++){
        NoHash *atual=tabelaHash->tabela[i].inicio;
        while(atual){
            int novoIndice=hash(atual->sala->codigo, novaCapacidade);
            insereLista(&novaTabela[novoIndice], atual->sala);
            atual=atual->prox;
        }
    }

    desalocarTabela(tabelaHash);
    tabelaHash->tabela=novaTabela;
    tabelaHash->capacidade=novaCapacidade;
}

void inserirHash(TabelaHash *tabelaHash, Sala *sala){
    if((float)tabelaHash->itens/tabelaHash->capacidade > FC_MAX){
        redimensionar(tabelaHash);
    }
    
    int id=hash(sala->codigo, tabelaHash->capacidade);
    insereLista(&tabelaHash->tabela[id], sala);
    tabelaHash->itens++;
}

char *buscarHash(TabelaHash *tabelaHash, int chave){
    int id=hash(chave, tabelaHash->capacidade);
    return buscarLista(&tabelaHash->tabela[id], chave);
}

void atualizarEstado(TabelaHash *tabelaHash, int sala, char *estado){
    int i = hash(sala, tabelaHash->capacidade); 
    NoHash *aux = tabelaHash->tabela[i].inicio;
    while (aux) {
        if (aux->sala->codigo == sala) { 
            aux->sala->estado = estado;
        }
        aux = aux->prox;
    }
}

void desalocarTabela(TabelaHash *tabelaHash){
    for(int i=0; i<tabelaHash->capacidade; i++){
        NoHash *atual=tabelaHash->tabela[i].inicio;
        while(atual){
            NoHash *temp=atual;
            atual=atual->prox;
            free(temp);
        }
    }
    free(tabelaHash->tabela);
}
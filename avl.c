#include "libraries.h"

No *alocaNo(Sala *sala){
    No *novo=(No*)malloc(sizeof(No));
    if(novo){
        novo->sala=sala;
        novo->esq=NULL;
        novo->dir=NULL;
        novo->altura=0;
    }else{
        printf("\nErro ao alocar nó");
        return 0;
    }
    return novo;
}

int maiorSub(int a, int b){
    return (a>b) ? a : b;
}

int alturaNo(No *no){
    if(no == NULL)
        return -1;
    else
        return no->altura;
}

int fator(No *no){
    if(no)
        return (alturaNo(no->esq) - alturaNo(no->dir));
    else
        return 0;
}

No *rotacaoEsq(No *raiz){
    No *pai, *filho;

    pai=raiz->dir;
    filho=pai->esq;
    
    pai->esq=raiz;
    raiz->dir=filho;

    raiz->altura=maiorSub(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;
    pai->altura=maiorSub(alturaNo(pai->esq), alturaNo(pai->dir)) + 1; 

    return pai;
}

No *rotacaoDir(No *raiz){
    No *pai, *filho;

    pai=raiz->esq;
    filho=pai->dir;

    pai->dir=raiz;
    raiz->esq=filho;

    raiz->altura=maiorSub(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;
    pai->altura=maiorSub(alturaNo(pai->esq), alturaNo(pai->dir)) + 1; 

    return pai;
}

No *rotacaoDirEsq(No *raiz){
    raiz->dir=rotacaoDir(raiz->dir);
    return rotacaoEsq(raiz);
}

No *rotacaoEsqDir(No *raiz){
    raiz->esq=rotacaoEsq(raiz->esq);
    return rotacaoDir(raiz);
}

No *inserirAVL(No *raiz, Sala *sala, TabelaHash *tabelaHash){
    if(raiz == NULL){
        raiz = alocaNo(sala);
        raiz->sala->estado="disponivel";
        inserirHash(tabelaHash, sala);
    }else{
        if(sala->codigo < raiz->sala->codigo){
            raiz->esq=inserirAVL(raiz->esq,sala,tabelaHash);
        }else if(sala->codigo>raiz->sala->codigo){
            raiz->dir=inserirAVL(raiz->dir, sala, tabelaHash);
        }else{
            printf("\nErro ao inserir %d", sala->codigo);
        }
    }

    raiz->altura=maiorSub(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;
    raiz=balancear(raiz);

    return raiz;
}

No *balancear(No *raiz){
    int fb=fator(raiz);

    if(fb<-1 && fator(raiz->dir) <=0)
        raiz=rotacaoEsq(raiz);
    else if(fb>1 && fator(raiz->esq)>=0)
        raiz=rotacaoDir(raiz);
    else if(fb>1 && fator(raiz->esq)<0)
        raiz=rotacaoEsqDir(raiz);
    else if(fb<-1 && fator(raiz->dir)>0)
        raiz=rotacaoDirEsq(raiz);
    return raiz;
}

No *buscarAVL(No *raiz, int codigo){
    if(raiz == NULL){
        printf("\nbusca = NULL");
        return NULL;
    }
    if(raiz->sala->codigo == codigo){
        return raiz;
    }
    if(codigo < raiz->sala->codigo){
        return buscarAVL(raiz->esq, codigo); 
    }else{
        return buscarAVL(raiz->dir, codigo);
    }
}

No *removerAVL(No *raiz, int sala){
    if(raiz == NULL){
        printf("\nValor nao encontrado");
        return NULL;
    }else{
        if(raiz->sala->codigo==sala){
            if(raiz->esq==NULL && raiz->dir==NULL){
                free(raiz);
                printf("\n%d removido", sala);
                return NULL;
            }else{
                if(raiz->esq!=NULL && raiz->dir!=NULL){
                    No *aux=raiz->esq;
                    while(aux->dir!=NULL){
                        aux=aux->dir;
                    }
                    Sala *salaAux;
                    salaAux=raiz->sala;
                    raiz->sala=aux->sala;
                    aux->sala=salaAux;
                    printf("\nNó %d trocado", sala);
                    raiz->esq=removerAVL(raiz->esq, sala);
                    return raiz;
                }else{
                    No *aux;
                    if(raiz->esq!=NULL)
                        aux=raiz->esq;
                    else
                        aux=raiz->dir;
                    free(raiz);
                    printf("\nNó com 1 filho removido");
                    return aux;
                }
            }
        }else{
            if(sala<raiz->sala->codigo)
                raiz->esq=removerAVL(raiz->esq, sala);
            else
                raiz->dir=removerAVL(raiz->dir, sala);
        }
        raiz->altura=maiorSub(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;
        raiz=balancear(raiz);
        return raiz;
    }
}

void desalocaAVL(No *raiz) {
    if(raiz){
        desalocaAVL(raiz->esq);
        desalocaAVL(raiz->dir); 
        free(raiz->sala);
        free(raiz);
    }
}

void escreverAVL(No *raiz, FILE *arq){
    if(raiz){
        escreverAVL(raiz->esq, arq);
        fprintf(arq, "\tSala: %d Capacidade: %d\n", raiz->sala->codigo, raiz->sala->capacidade);
        escreverAVL(raiz->dir, arq);
    }
}

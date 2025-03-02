#include "libraries.h"

int main(){
    int valor, cod, cap, prioridade;
    char opcao[21], linha[30], *estado;
    No *raiz=NULL;
    No *busca=NULL;
    Sala *sala;
    MaxHeap *heap=criarHeap(10);
    TabelaHash *tabelaHash = (TabelaHash*)malloc(sizeof(TabelaHash));
    if(!tabelaHash)
        printf("Erro ao alocar tabela hash");
    iniciaTabela(tabelaHash, 1);

    FILE *arq = fopen("Arquivos/entrada1.txt", "r");

    if(!arq){
        printf("Erro ao abrir arquivo");
        return 1;
    }

    while(fgets(linha, sizeof(linha), arq)){
        cod=0;
        sscanf(linha, "%s", opcao);
        printf("\nOpcao escolhida: %s", opcao);
        if(strcmp(opcao, "CRIAR_SALA") == 0){
            sala=(Sala*)malloc(sizeof(Sala));
            if(!sala){
                printf("\nErro ao alocar sala");
                return 1;
            }
            sscanf(linha, "%*s %d %d", &sala->codigo, &sala->capacidade);
            raiz = inserirAVL(raiz,sala,tabelaHash);
            outputLog(opcao, sala->codigo, 0, sala->capacidade, sala->estado, 0, 0);
        }else if(strcmp(opcao, "RESERVAR_SALA") == 0){
            sscanf(linha, "%*s %d %d", &cod, &prioridade);
            busca = buscarAVL(raiz, cod);
            busca->sala->prioridade=prioridade;
            inserirHeap(heap, busca->sala, prioridade);
            outputLog(opcao, cod, prioridade, 0, "", 0, 0);
        }else if(strcmp(opcao, "BLOQUEAR_SALA") == 0){
            sscanf(linha, "%*s %d", &cod);
            atualizarEstado(tabelaHash, cod, "bloqueada");
            estado=buscarHash(tabelaHash, cod);
            outputLog(opcao, cod, 0, 0, estado/*"bloqueada"*/, 0, 0);
        }else if(strcmp(opcao, "DESBLOQUEAR_SALA") == 0){
            sscanf(linha, "%*s %d", &cod);
            atualizarEstado(tabelaHash, cod, "disponivel");
            estado=buscarHash(tabelaHash, cod);
            outputLog(opcao, cod, 0, 0, estado, 0, 0);
        }else if(strcmp(opcao, "CANCELAR_RESERVA") == 0){
            sscanf(linha, "%*s %d", &cod);
            busca = buscarAVL(raiz, cod);
            cancelarHeap(heap, busca->sala->codigo);
            outputLog(opcao, cod, 0, 0, 0, 0, 0);
        }else if(strcmp(opcao, "CONSULTAR_SALA") == 0){
            sscanf(linha, "%*s %d", &cod);
            estado = buscarHash(tabelaHash, cod);
            outputLog(opcao, cod, 0, 0, estado, 0, 0);
        }else if(strcmp(opcao, "LISTAR_SALAS") == 0){
            outputLog(opcao, 0, 0, 0, "", raiz, 0);
        }else if(strcmp(opcao, "LISTAR_RESERVAS") == 0){
            outputLog(opcao, 0, 0, 0, "", 0, heap);
        }else if(strcmp(opcao, "ATUALIZAR_PRIORIDADE") == 0){
            sscanf(linha, "%*s %d %d", &cod, &prioridade);
            busca = buscarAVL(raiz, cod);
            if(busca){
                atualizarPrioridade(heap, busca->sala->codigo, prioridade);
                outputLog(opcao, cod, prioridade, 0, "", 0, 0);
            }
        }else{
            printf("\nErro ao ler arquivo");
        }
    }

    fclose(arq);

    desalocarTabela(tabelaHash);
    free(tabelaHash);
    desalocarHeap(heap);
    desalocaAVL(raiz);

    return 0;
}


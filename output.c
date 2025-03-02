#include "libraries.h"

void outputLog(char *opcao, int codigo, int prioridade, int capacidade, char *estado, No *raiz, MaxHeap *heap){
    FILE *log=fopen("saida.txt", "a");
    if(!log){
        printf("\nErro ao ao abrir log");
        return;
    }
    if(strcmp(opcao, "CRIAR_SALA") == 0){
        fprintf(log, "%s %d %d %s\n", opcao, codigo, capacidade, estado);
    }else if(strcmp(opcao, "RESERVAR_SALA") == 0){
        fprintf(log, "%s %d %d\n", opcao, codigo, prioridade);
    }else if(strcmp(opcao, "BLOQUEAR_SALA") == 0){
        fprintf(log, "%s %d %s\n", opcao, codigo, estado);
    }else if(strcmp(opcao, "DESBLOQUEAR_SALA") == 0){
        fprintf(log, "%s %d %s\n", opcao, codigo, estado);
    }else if(strcmp(opcao, "CANCELAR_RESERVA") == 0){
        fprintf(log, "%s %d\n", opcao, codigo);
    }else if(strcmp(opcao, "CONSULTAR_SALA") == 0){
        fprintf(log, "%s %d %s\n", opcao, codigo, estado);
    }else if(strcmp(opcao, "LISTAR_SALAS") == 0){
        fprintf(log, "Salas e capacidades:\n");
        escreverAVL(raiz, log);
    }else if(strcmp(opcao, "LISTAR_RESERVAS") == 0){
        fprintf(log, "Salas e prioridades:\n");
        escreverHeap(heap, log);
    }else if(strcmp(opcao, "ATUALIZAR_PRIORIDADE") == 0){
        fprintf(log, "%s %d %d\n", opcao, codigo, prioridade);
    }else{
        printf("\nErro do krl");
    }

    fclose(log);
}


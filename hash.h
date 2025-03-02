#ifndef HASH_H
#define HASH_H

/**
 * @brief Struct para o No dentro da Tabela Hash
 * @typedef NoHash
*/
typedef struct no_hash NoHash;

/**
 * @brief Struct para a Lista dentro da Tabela Hash
 * @typedef Lista
*/
typedef struct lista Lista;

/**
 * @brief Struct para a Tabela Hash
 * @typedef TabelaHash
*/
typedef struct tabela_hash{
    Lista *tabela;
    int capacidade;
    int itens;
}TabelaHash;

/**
 * @brief Inicia a lista encadeada
 * @param lista
 * @return void
*/
void iniciaLista(Lista *lista);

/**
 * @brief Insere uma sala em uma lista
 * @param lista, sala
 * @return void
*/
void insereLista(Lista *lista, Sala *sala);

/**
 * @brief Busca uma lista dentro da hash
 * @param lista, chave
 * @return char
*/
char *buscarLista(Lista *lista, int chave);

/**
 * @brief Inicia a tabela hash
 * @param tabelaHash, capacidade
 * @return void
*/
void iniciaTabela(TabelaHash *tabelaHash, int capacidade);

/**
 * @brief Calcula a posicao em que determinada chave sera inserida
 * @param chave, capacidade
 * @return int
*/
int hash(int chave, int capacidade);

/**
 * @brief Redimensiona a tabela hash para armazenar mais valores
 * @param tabelaHash
 * @return void
*/
void redimensionar(TabelaHash *tabelaHash); 

/**
 * @brief Insere uma sala na tabela hash
 * @param tabelaHash, sala
 * @return void
*/
void inserirHash(TabelaHash *tabelaHash, Sala *sala);

/**
 * @brief Busca por uma posicao na tabela hash
 * @param tabelaHash, chave
 * @return char
*/
char *buscarHash(TabelaHash *tabelaHash, int chave);

/**
 * @brief Atualiza o estado de uma sala
 * @param tabelaHash, sala, estado
 * @return void
*/
void atualizarEstado(TabelaHash *tabelaHash, int sala, char *estado);

/**
 * @brief Desaloca a tabela hash
 * @param tabelaHash
 * @return void
*/
void desalocarTabela(TabelaHash *tabelaHash);

#endif
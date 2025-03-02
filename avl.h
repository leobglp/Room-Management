#ifndef AVL_H
#define AVL_H

/**
 * @brief Struct para a Tabela Hash
 * @typedef TabelaHash
*/
typedef struct tabela_hash TabelaHash;

/**
 * @brief Struct para a sala
 * @typedef Sala
*/
typedef struct sala{
    int codigo;
    int capacidade;
    int prioridade;
    char *estado;
}Sala;

/**
 * @brief Struct para o No da AVL
 * @typedef No
*/
typedef struct no{
    int altura;
    Sala *sala;
    struct no *esq, *dir;
}No;

/**
 * @brief Aloca uma sala em um nó
 * @param sala
 * @return No
*/
No *alocaNo(Sala *sala);

/**
 * @brief Retorna a maior subarvore
 * @param   a, b
 * @return int
*/
int maiorSub(int a, int b);

/**
 * @brief Calcula o a altura de um no
 * @param no
 * @return int
*/
int alturaNo(No *no);

/**
 * @brief Calcula o fator de balanceamento
 * @param no
 * @return int
*/
int fator(No *no);

/**
 * @brief Rotaciona a AVL para a esquerda
 * @param raiz
 * @return No
*/
No *rotacaoEsq(No *raiz);

/**
 * @brief Rotaciona a AVL para a direita
 * @param raiz
 * @return No
*/
No *rotacaoDir(No *raiz);

/**
 * @brief Rotacao dupla da direita para a esquerda
 * @param raiz
 * @return No
*/
No *rotacaoDirEsq(No *raiz);

/**
 * @brief Rotacao dupla da esquerda para a direita
 * @param raiz
 * @return No
*/
No *rotacaoEsqDir(No *raiz);

/**
 * @brief Insere uma sala na AVL
 * @param raiz, sala, tabelaHash
 * @return No
*/
No *inserirAVL(No *raiz, Sala *sala, TabelaHash *tabelaHash);

/**
 * @brief Balanceamento da AVL
 * @param raiz
 * @return No
*/
No *balancear(No *raiz);

/**
 * @brief Busca uma sala pelo codigo na AVL
 * @param raiz, codigo
 * @return No
*/
No *buscarAVL(No *raiz, int codigo);

/**
 * @brief Remove uma sala da AVL
 * @param raiz, sala
 * @return No
*/
No *removerAVL(No *raiz, int sala);

/**
 * @brief Desaloca a AVL
 * @param raiz, sala
 * @return void
*/
void desalocaAVL(No *raiz);

/**
 * @brief Escreve a AVL no arquivo de saida
 * @param raiz, arq
 * @return void
*/
void escreverAVL(No *raiz, FILE *arq);

#endif
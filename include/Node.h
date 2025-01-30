#ifndef NODE_H
#define NODE_H

/**
 * @brief Estrutura do nó para as matrizes esparsas.
 */
struct Node {
    int linha;      ///< Índice da linha do nó.
    int coluna;     ///< Índice da coluna do nó.
    double valor;   ///< Valor armazenado no nó.
    Node* abaixo;   ///< Ponteiro para o nó abaixo na matriz.
    Node* direito;  ///< Ponteiro para o nó à direita na matriz.

    /**
     * @brief Construtor padrão do nó.
     *
     * Inicializa o nó com os valores de linha e coluna fornecidos.
     * Os ponteiros `abaixo` e `direito` apontam para o próprio nó.
     *
     * @param lin Índice da linha do nó.
     * @param col Índice da coluna do nó.
     */
    Node(int lin, int col)
        : linha(lin), coluna(col), abaixo(this), direito(this) {}

    /**
     * @brief Construtor do nó com valor.
     *
     * Inicializa o nó com os valores de linha, coluna e valor fornecidos.
     * Os ponteiros `abaixo` e `direito` apontam para o próprio nó.
     *
     * @param lin Índice da linha do nó.
     * @param col Índice da coluna do nó.
     * @param value Valor a ser armazenado no nó.
     */
    Node(int lin, int col, double value) : Node(lin, col) {
        this->valor = value;
    }
};

#endif
#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <stdexcept>
#include <string>

#include "Node.h"

/**
 * @brief Classe que representa uma matriz esparsa 2D.
 */
class SparseMatrix {
   private:
    Node* m_head = new Node(0, 0);  // Inicializa o nó "sentinela" sem valor.
    int linhas = 0;                 // Inicializa linhas com o valor 0.
    int colunas = 0;                // Inicializa colunas com o valor 0.

    /**
     * @brief Inicializa a matriz.
     *
     * Esta função aloca memória para um nó sentinela em cada coluna n
     * e cada linha m, faz cada nó adicionado apontar para o nó anterior
     * e o nó m_head apontar para o último adicionado.
     *
     * @param m Quantidade de linhas da matriz esparsa.
     * @param n Quantidade de colunas da matriz esparsa.
     */
    void initializeMatrix(int m, int n);
    void clear();

   public:
    /**
     * @brief Construtor default da classe SparseMatrix.
     */
    SparseMatrix() = default;

    /**
    * @brief Construtor da classe SparseMatrix.
    * 
    * Essa função verifica se os valores de linha e coluna (m e n
    * respectivamente) são válidos e inicializa (aloca espaço na memória)
    * os nós sentinelas de cada linha e coluna.
    *
    * @param m Quantidade de linhas para a matriz esparsa.
    * @param n Quantidade de colunas para a matriz esparsa.
    */
    SparseMatrix(int m, int n);

    SparseMatrix(const SparseMatrix& matrix);

    /**
    * @brief Destrutor da classe SparseMatrix.
    *
    * Essa função apaga (desaloca a memória) os nós de cada linha e coluna
    * (m e n respectivamente) e consequentemente a matriz.
    */
    ~SparseMatrix();

   /**
    * @brief Função de inserção.
    *
    * @param i Linha da matriz.
    * @param j Coluna da matriz.
    * @param value Valor a ser adicionado.
    */
    void insert(int i, int j, double value);

   /**
    * @brief Imprime a matriz no terminal.
    */
    void print();

   /**
    * @brief ?
    */
    double get(int i, int j);

    int getLines() const;
    int getCols() const;
    int size() const;

    /**
     * @brief Sobrecarga do operador de atribuição (=).
     *
     * Este operador permite atribuir uma matriz esparsa a outra, copiando      * os dados da matriz recebida.
     *
     * @param matrix Referência constante para uma matriz esparsa a ser
     * copiada.
     * @return Referência para a instância atual da matriz esparsa.
     */
    SparseMatrix& operator=(const SparseMatrix& matrix);
};

#endif

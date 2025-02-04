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
    Node* m_head = new Node(0, 0);  //> Inicializa um nó sentinela sem valor.
    int linhas = 0;                 //> Inicializa linhas com o valor 0.
    int colunas = 0;                //> Inicializa colunas com o valor 0.

    /**
     * @brief Inicializa a matriz esparsa com nós sentinelas para linhas e
     * colunas.
     *
     * Esta função cria nós sentinelas para cada linha e coluna da matriz,
     * conectando-os de forma circular. Os nós sentinelas serão usados para
     * facilitar a navegação e inserção de elementos na matriz esparsa.
     */
    void initializeMatrix();

    /**
     * @brief Limpa a matriz, liberando a memória de todos os nós.
     *
     * Percorre todas as linhas e colunas da matriz, deletando os nós com
     * valores e os nós sentinelas.
     */
    void clear();

   public:
    /**
     * @brief Construtor padrão da classe SparseMatrix.
     *
     * Este construtor inicializa a classe com valores padrão.
     */
    SparseMatrix() = default;

    /**
     * @brief Construtor da classe SparseMatrix que recebe parâmetros.
     *
     * Inicializa a matriz com o número de linhas e colunas especificado.
     * Lança uma exceção se os valores de linhas ou colunas forem inválidos.
     *
     * @param m Número de linhas da matriz.
     * @param n Número de colunas da matriz.
     * @throws std::out_of_range Se m ou n forem menores ou iguais a zero.
     */
    SparseMatrix(int m, int n);

    /**
     * @brief Construtor de cópia da classe SparseMatrix.
     *
     * Cria uma nova matriz esparsa como cópia de outra matriz.
     * A nova matriz terá os mesmos valores não nulos da matriz original.
     *
     * @param matrix Matriz esparsa a ser copiada.
     */
    SparseMatrix(const SparseMatrix& matrix);

    /**
     * @brief Destrutor da classe SparseMatrix.
     *
     * Libera toda a memória alocada para os nós da matriz, incluindo os
     * nós sentinelas.
     */
    ~SparseMatrix();

    /**
     * @brief Insere um valor na matriz esparsa.
     *
     * Insere um valor na posição (i, j) da matriz. Se o valor for zero,
     * o nó correspondente é removido da matriz. Lança uma exceção se
     * os índices forem inválidos.
     *
     * @param i Índice da linha (1-based).
     * @param j Índice da coluna (1-based).
     * @param value Valor a ser inserido.
     * @throws std::out_of_range Se i ou j forem inválidos.
     */
    void insert(int i, int j, double value);

    /**
     * @brief Obtém o valor de uma posição na matriz.
     *
     * Retorna o valor armazenado na posição (i, j) da matriz.
     * Se a posição não contiver um valor, retorna zero.
     * Lança uma exceção se os índices forem inválidos.
     *
     * @param i Índice da linha (1-based).
     * @param j Índice da coluna (1-based).
     * @return Valor na posição (i, j) ou zero se a posição estiver vazia.
     * @throws std::out_of_range Se i ou j forem inválidos.
     */
    double get(int i, int j) const;

    /**
     * @brief Retorna o número de linhas da matriz.
     *
     * @return Número de linhas da matriz.
     */
    int getLines() const;

    /**
     * @brief Retorna o número de colunas da matriz.
     *
     * @return Número de colunas da matriz.
     */
    int getCols() const;

    /**
     * @brief Retorna o tamanho total da matriz (linhas * colunas).
     *
     * @return Tamanho total da matriz.
     */
    int size() const;

    /**
     * @brief Imprime a matriz no terminal.
     *
     * Percorre a matriz e imprime seus valores no formato de matriz
     * bidimensional. Valores não presentes na matriz esparsa são impressos como
     * zero.
     */
    void print() const;

    /**
     * @brief Sobrecarga do operador de atribuição.
     *
     * Atribui os valores de outra matriz esparsa à atual.
     * Libera a memória da matriz atual antes de copiar os valores.
     *
     * @param matrix Matriz esparsa a ser copiada.
     * @return Referência para a instância atual.
     */
    SparseMatrix& operator=(const SparseMatrix& matrix);
};

#endif

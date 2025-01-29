#include "../include/SparseMatrix.h"

#include <iostream>
#include <stdexcept>

/**
 * @brief Inicializa a matriz esparsa com nós sentinelas para linhas e colunas.
 *
 * Esta função cria nós sentinelas para cada linha e coluna da matriz,
 * conectando-os de forma circular. Os nós sentinelas serão usados para facilitar
 * a navegação e inserção de elementos na matriz esparsa.
 *
 * @param m Número de linhas da matriz.
 * @param n Número de colunas da matriz.
 */
void SparseMatrix::initializeMatrix(int m, int n) {
    for (int i = m + n; i >= 1; i--) {
        if (i > n) {
            Node* aux = new Node(0, i - n);
            aux->direito = m_head->direito;
            m_head->direito = aux;
        } else {
            Node* aux = new Node(i, 0);
            aux->abaixo = m_head->abaixo;
            m_head->abaixo = aux;
        }
    }
}

/**
 * @brief Construtor da classe SparseMatrix.
 *
 * Inicializa a matriz com o número de linhas e colunas especificado.
 * Lança uma exceção se os valores de linhas ou colunas forem inválidos.
 *
 * @param m Número de linhas da matriz.
 * @param n Número de colunas da matriz.
 * @throws std::out_of_range Se m ou n forem menores ou iguais a zero.
 */
SparseMatrix::SparseMatrix(int m, int n) : linhas(m), colunas(n) {
    if (m <= 0 || n <= 0) throw std::out_of_range("Invalid line or column");
    initializeMatrix(m, n);
}

/**
 * @brief Construtor de cópia da classe SparseMatrix.
 *
 * Cria uma nova matriz esparsa como cópia de outra matriz.
 * A nova matriz terá os mesmos valores não nulos da matriz original.
 *
 * @param matrix Matriz esparsa a ser copiada.
 */
SparseMatrix::SparseMatrix(const SparseMatrix& matrix)
    : SparseMatrix(matrix.linhas, matrix.colunas) {
    if (this != &matrix) {
        Node* auxL = matrix.m_head->abaixo;
        while (auxL != matrix.m_head) {
            Node* auxC = auxL->direito;
            while (auxC != auxL) {
                insert(auxC->linha, auxC->coluna, auxC->valor);
                auxC = auxC->direito;
            }
            auxL = auxL->abaixo;
        }
    }
}

/**
 * @brief Destrutor da classe SparseMatrix.
 *
 * Libera toda a memória alocada para os nós da matriz, incluindo os nós sentinelas.
 */
SparseMatrix::~SparseMatrix() {
    clear();
    delete m_head;
}

/**
 * @brief Limpa a matriz, liberando a memória de todos os nós.
 *
 * Percorre todas as linhas e colunas da matriz, deletando os nós com valores
 * e os nós sentinelas.
 */
void SparseMatrix::clear() {
    Node* col = m_head->direito;
    while (col != m_head) {
        Node* atual = col->abaixo;
        while (atual != col) {
            Node* temp = atual;
            atual = atual->abaixo;
            delete temp; 
        }

        Node* temp = col;
        col = col->direito;
        delete temp; 
    }

    Node* linha = m_head->abaixo;  
    while (linha != m_head) {      
        Node* temp = linha;
        linha = linha->abaixo;
        delete temp;  
    }

    m_head->direito = m_head;
    m_head->abaixo = m_head;
}

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
void SparseMatrix::insert(int i, int j, double value) {
    
    if (i <= 0 || i > linhas || j <= 0 || j > colunas) {
        throw std::out_of_range("Invalid line or column");
    }

    Node* aux = m_head->direito;

    
    while (aux->coluna != j) { aux = aux->direito; }

    
    while (aux->abaixo->linha != 0 && aux->abaixo->linha < i) {
        aux = aux->abaixo;
    }

    
    if (aux->abaixo->linha == i) {
        if (value != 0) {
            aux->abaixo->valor = value;
        } else {
            Node* toErase = aux->abaixo;
            aux->abaixo = toErase->abaixo;

            aux = m_head->abaixo;
            while (aux->linha != i) { aux = aux->abaixo; }
            while (aux->direito->coluna != 0 && aux->direito->coluna < j) {
                aux = aux->direito;
            }
            aux->direito = toErase->direito;

            delete toErase;
        }
        return;
    }
    
    Node* temp = new Node(i, j, value);
    temp->abaixo = aux->abaixo;
    aux->abaixo = temp;

    aux = m_head->abaixo;
    while (aux->linha != i) { aux = aux->abaixo; }
    while (aux->direito->coluna != 0 && aux->direito->coluna < j) {
        aux = aux->direito;
    }

    temp->direito = aux->direito;
    aux->direito = temp;
}

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
double SparseMatrix::get(int i, int j) {
    if (i <= 0 || i > linhas || j <= 0 || j > colunas) {
        throw std::out_of_range("Invalid line or column");
    }

    Node* aux_linha = m_head->abaixo;
    while (aux_linha->linha != m_head->linha && aux_linha->linha < i)
        aux_linha = aux_linha->abaixo;

    if (aux_linha == m_head || aux_linha->linha != i) return 0;

    Node* aux_coluna = aux_linha->direito;
    while (aux_coluna != aux_linha && aux_coluna->coluna < j)
        aux_coluna = aux_coluna->direito;

    if (aux_coluna == aux_linha || aux_coluna->coluna != j) return 0;

    return aux_coluna->valor;
}

/**
 * @brief Imprime a matriz no terminal.
 *
 * Percorre a matriz e imprime seus valores no formato de matriz bidimensional.
 * Valores não presentes na matriz esparsa são impressos como zero.
 */
void SparseMatrix::print() {
    Node* aux = m_head->abaixo;
    for (int i = 1; i <= linhas; i++) {
        Node* temp = aux->direito;

        std::cout << "[ ";
        for (int j = 1; j <= colunas; j++) {
            if (temp->coluna == j)
                std::cout << temp->valor << " ";
            else
                std::cout << 0 << " ";

            if (j == temp->coluna) temp = temp->direito;
        }
        aux = aux->abaixo;
        std::cout << ']' << std::endl;
    }
}

/**
 * @brief Sobrecarga do operador de atribuição.
 *
 * Atribui os valores de outra matriz esparsa à atual.
 * Libera a memória da matriz atual antes de copiar os valores.
 *
 * @param matrix Matriz esparsa a ser copiada.
 * @return Referência para a instância atual.
 */
SparseMatrix& SparseMatrix::operator=(const SparseMatrix& matrix) {
    if (this != &matrix) {
        clear();
        linhas = matrix.linhas;
        colunas = matrix.colunas;
        initializeMatrix(linhas, colunas);

        Node* auxL = matrix.m_head->abaixo;
        while (auxL != matrix.m_head) {
            Node* auxC = auxL->direito;
            while (auxC != auxL) {
                insert(auxC->linha, auxC->coluna, auxC->valor);
                auxC = auxC->direito;
            }
            auxL = auxL->abaixo;
        }
    }

    return *this;
}

/**
 * @brief Retorna o número de linhas da matriz.
 *
 * @return Número de linhas da matriz.
 */
int SparseMatrix::getLines() const {
    return linhas;
}

/**
 * @brief Retorna o número de colunas da matriz.
 *
 * @return Número de colunas da matriz.
 */
int SparseMatrix::getCols() const {
    return colunas;
}

/**
 * @brief Retorna o tamanho total da matriz (linhas * colunas).
 *
 * @return Tamanho total da matriz.
 */
int SparseMatrix::size() const {
    return linhas * colunas;
}

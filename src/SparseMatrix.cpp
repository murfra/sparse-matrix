#include "../include/SparseMatrix.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

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

SparseMatrix::SparseMatrix(int m, int n) : linhas(m), colunas(n) {
    if (m <= 0 || n <= 0) throw std::out_of_range("Invalid line or column");
    initializeMatrix(m, n);
}

SparseMatrix::SparseMatrix(const SparseMatrix& matrix)
    : linhas(matrix.linhas), colunas(matrix.colunas) {
    if (this != &matrix) {
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
}

SparseMatrix::~SparseMatrix() {
    clear();
    delete m_head;
}

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

int SparseMatrix::getLines() const {
    return linhas;
}

int SparseMatrix::getCols() const {
    return colunas;
}

int SparseMatrix::size() const {
    return linhas * colunas;
}

void SparseMatrix::print() {
    Node* aux = m_head->abaixo;
    std::ostringstream buff;

    for (int i = 1; i <= linhas; i++) {
        Node* temp = aux->direito;
        buff << "[ ";
        for (int j = 1; j <= colunas; j++) {
            if (temp->coluna == j) buff << temp->valor << ' ';
            else buff << "0 ";

            if (j == temp->coluna) temp = temp->direito;
        }
        aux = aux->abaixo;
        buff << "]\n";
    }

    std::cout << buff.str();
}

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

/*
 * Autores:
 * - Carlos D. Rodrigues (Matrícula: 566429)
 * - Murilo Fragoso (Matrícula: 570701)
 *
 * Descrição:
 * Esse código aplica conceitos de lista simplesmente encadeada para
 * implementar matrizes esparsas.
 */

#ifdef _WIN32
#include <Windows.h>
#endif

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../include/SparseMatrix.h"

using namespace std;

/**
 * @brief Lê uma matriz esparsa de um arquivo e a armazena em uma SparseMatrix.
 *
 * Esta função abre um arquivo, lê as dimensões da matriz e seus valores não nulos,
 * e insere esses valores na matriz esparsa fornecida.
 *
 * @param m Referência para a SparseMatrix que será preenchida.
 * @param filename Nome do arquivo contendo os dados da matriz.
 * @throws std::runtime_error Se o arquivo não puder ser aberto.
 */
void readSparseMatrix(SparseMatrix &m, string filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Arquivo inválido ou não encontrado!");
    }

    int lin, col, i, j;
    double v;

    file >> lin >> col;
    m = SparseMatrix(lin, col);

    while (file >> i >> j >> v) m.insert(i, j, v);
}

/**
 * @brief Realiza a soma de duas matrizes esparsas.
 *
 * Esta função soma duas matrizes esparsas A e B, desde que tenham as mesmas dimensões.
 * O resultado é armazenado em uma nova matriz esparsa C.
 *
 * @param A Primeira matriz.
 * @param B Segunda matriz.
 * @return Ponteiro para a matriz resultante.
 */
SparseMatrix *sum(SparseMatrix &A, SparseMatrix &B) {
    if (A.getCols() == B.getCols() && A.getLines() == B.getLines()) {
        SparseMatrix *C = new SparseMatrix(A.getLines(), A.getCols());

        for (int i = 1; i <= C->getLines(); i++) {
            for (int j = 1; j <= C->getCols(); j++) {
                C->insert(i, j, (A.get(i, j) + B.get(i, j)));
            }
        }

        return C;
    } else {
        cout << "Não é possível somar matrizes de dimensões distintas ;("
             << "Só é possível caso seja 2x2, 3x3 e por assim vai..." << endl;
        return new SparseMatrix();
    }
}

/**
 * @brief Realiza a multiplicação de duas matrizes esparsas.
 *
 * Esta função multiplica duas matrizes esparsas A e B, desde que o número de colunas
 * de A seja igual ao número de linhas de B. O resultado é armazenado em uma nova matriz esparsa C.
 *
 * @param A Primeira matriz.
 * @param B Segunda matriz.
 * @return Ponteiro para a matriz resultante.
 */
SparseMatrix *multiply(SparseMatrix &A, SparseMatrix &B) {
    if (A.getCols() != B.getLines()) {
        cout << "Não é possível multiplicar as matrizes ;("
             << "O número de colunas da matriz A deve ser igual ao número de "
                "linhas da matriz B."
             << endl;
        return nullptr;
    }

    SparseMatrix *C = new SparseMatrix(A.getLines(), B.getCols());

    for (int i = 1; i <= A.getLines(); i++) {
        for (int j = 1; j <= B.getCols(); j++) {
            double soma = 0;

            for (int k = 1; k <= A.getCols(); k++) {
                soma += A.get(i, k) * B.get(k, j);
            }

            C->insert(i, j, soma);
        }
    }

    return C;
}

/**
 * @brief Exibe o menu inicial do programa.
 *
 * Esta função exibe uma mensagem de boas-vindas e instruções básicas para o usuário.
 */
void displayMenu() {
    cout << "Olá, seja bem-vindo(a)!\n";
    cout << "ATENÇÃO: Caso precise ver os comandos digite: ajuda\n";
    cout << setfill('-') << setw(51) << "" << endl;
}

/**
 * @brief Exibe a ajuda do programa.
 *
 * Esta função exibe as opções de uso do programa, incluindo como ler um arquivo
 * e outras funcionalidades disponíveis.
 */
void help() {
    cout << "uso:\n"
         << setw(2) << ""
         << "./sparse_matrix [-h | --help] [-f | --file]\n";

    cout << "\n" << setw(2) << "" << "-h, --help" << setw(20) << "";
    cout << "Mostra opções de ajuda\n";
    cout << setw(2) << "" << "-f, --file <ARQUIVO>" << setw(10) << "";
    cout << "Lê um ARQUIVO que especifica uma matriz" << endl;
}

/**
 * @brief Exibe a lista de comandos disponíveis no programa.
 *
 * Esta função lista todos os comandos que o usuário pode utilizar para interagir
 * com o programa, como criar matrizes, inserir valores, somar, multiplicar, etc.
 */
void comandos() {
    cout << setfill(' ') << "\nComandos disponíveis:\n"
         << setw(2) << "" << "[ajuda | help]" << setw(17) << ""
         << "Exibe esta lista de comandos\n"
         << setw(2) << "" << "[create] <m> <n>" << setw(15) << ""
         << "Cria uma matriz esparsa com m linhas e n colunas\n"
         << setw(2) << "" << "[size] <i>" << setw(21) << ""
         << "Exibe o tamanho da matriz de índice i\n"
         << setw(2) << "" << "[insert] <i> <m> <n> <v>" << setw(7) << ""
         << "Insere o valor v na célula (m, n) da matriz de índice i\n"
         << setw(2) << "" << "[get] <i> <m> <n>" << setw(14) << ""
         << "Obtém o valor na célula (m, n) da matriz de índice i\n"
         << setw(2) << "" << "[print] <i>" << setw(20) << ""
         << "Exibe a matriz de índice i\n"
         << setw(2) << "" << "[sum] <a> <b>" << setw(18) << ""
         << "Soma as matrizes de índices a e b e armazena o resultado\n"
         << setw(2) << "" << "[multiply] <a> <b>" << setw(13) << ""
         << "Multiplica as matrizes de índices a e b e armazena o resultado\n"
         << setw(2) << "" << "[show]" << setw(25) << ""
         << "Exibe todas as matrizes armazenadas\n"
         << setw(2) << "" << "[exit]" << setw(25) << ""
         << "Sai do programa e libera a mémoria\n";
}

/**
 * @brief Função principal do programa.
 *
 * Esta função gerencia a execução do programa, incluindo a leitura de argumentos
 * da linha de comando, a interação com o usuário e a execução dos comandos.
 *
 * @param argc Número de argumentos da linha de comando.
 * @param argv Vetor de argumentos da linha de comando.
 * @return 0 se o programa for executado com sucesso.
 */
int main(int argc, char const *argv[]) {
    // Configuração de caracteres especiais para Windowns
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    std::cout << "Configurado para caracteres especiais e acentos. 😊" << endl;
#endif

    vector<SparseMatrix> matrizes;

    if (argc > 1) {
        string arg1 = string(argv[1]);
        if (arg1 == "-h" || arg1 == "--help") {
            help();
            return 0;
        } else {
            displayMenu();
            // leitura do arquivo
            if (arg1.find("--file=") == 0) {
                matrizes.push_back(SparseMatrix());
                readSparseMatrix(matrizes[0], arg1.substr(7));
                cout << "Arquivo carregado!" << endl;
            } else if (arg1 == "-f" || arg1 == "--file") {
                matrizes.push_back(SparseMatrix());
                readSparseMatrix(matrizes[0], argv[2]);
                cout << "Arquivo carregado!" << endl;
            }
        }
    } else
        displayMenu();

    while (true) {
        cout << "> ";

        string comando, token;
        getline(cin, comando);
        stringstream ss{comando};
        ss >> token;

        cout << "$" << ss.str() << " ✅" << endl;

        // exit
        if (token == "exit") {
            cout << "Encerrando o programa... ⏳" << endl;
            matrizes.clear();
            cout << "🔔 Programa encerrado. Até logo!" << endl;
            break;
        }

        // create m, n
        else if (token == "create") {
            int m, n;
            ss >> m >> n;
            matrizes.push_back(SparseMatrix(m, n));
        }

        // size
        else if (token == "size") {
            int i;
            ss >> i;
            cout << "Tamanho da matriz " << i << ": " << matrizes[i].size()
                 << endl;
        }

        // insert i, j, v(valor) l
        else if (token == "insert") {
            int i, m, n;
            double v;
            ss >> i >> m >> n >> v;
            matrizes[i].insert(m, n, v);
        }

        // get da célula i, j
        else if (token == "get") {
            int i, m, n;
            ss >> i >> m >> n;
            cout << "Valor na célula (" << m << ", " << n
                 << ") é: " << matrizes[i].get(m, n) << endl;
        }

        // print matriz i
        else if (token == "print") {
            int i;
            ss >> i;
            matrizes[i].print();
        }

        // somar matrizes A e B
        else if (token == "sum") {
            int a, b;
            ss >> a >> b;
            SparseMatrix *resultado = sum(matrizes[a], matrizes[b]);
            if (resultado != nullptr) {
                matrizes.push_back(*resultado);
                delete resultado;
            }
        }

        // multiplicar matrizes A e B
        else if (token == "multiply") {
            int a, b;
            ss >> a >> b;
            SparseMatrix *resultado = multiply(matrizes[a], matrizes[b]);
            if (resultado != nullptr) {
                matrizes.push_back(*resultado);
                delete resultado;
            }
        }

        // exibir matrizes
        else if (token == "show") {
            auto index = 0;
            for (auto &matrix : matrizes) {
                cout << "matriz[" << index++ << "] :" << endl;
                matrix.print();
            }
        }

        // comandos disponíveis
        else if (token == "ajuda" || token == "help") {
            comandos();
        }

        else {
            cout << "O comando que você inseriu é inválido/não existe ❌ "
                 << endl;
        }
    }
    return 0;
}

# 🌀 **Matriz Esparsa Circular com Nós Sentinela** 🚀  
## **Trabalho de Estrutura de Dados do 2º semestre de Ciência da Computação**
### Implementação em C++ | Relatório SBC | Apresentação Pessoal  

---

## 📋 **Descrição do Projeto**  
Este projeto consiste na implementação de um **Tipo Abstrato de Dados (TAD)** para uma **Matriz Esparsa Circular** utilizando **nós sentinela**. A matriz esparsa é uma estrutura de dados eficiente para armazenar matrizes com grande quantidade de elementos nulos, reduzindo o consumo de memória e otimizando operações de acesso e manipulação. A adição de nós sentinela e a estrutura circular visam melhorar a eficiência e a consistência das operações realizadas sobre a matriz.

O trabalho foi desenvolvido como parte da avaliação da disciplina de **Estruturas de Dados** na **Universidade Federal do Ceará (UFC) - Campus de Quixadá**, sob a orientação do professor Atílio Gomes Luiz. Além da implementação, foi produzido um **relatório técnico** no formato da **Sociedade Brasileira de Computação (SBC)** e uma **apresentação** para demonstração dos resultados.

---

## 🛠️ **Funcionalidades Implementadas**  
- **Inserção de elementos**: Adição de valores em posições específicas da matriz.  
- **Remoção de elementos**: Remoção de valores em posições específicas.  
- **Consulta de elementos**: Acesso eficiente aos valores armazenados.  
- **Navegação circular**: Utilização de nós sentinela para facilitar a navegação e operações na matriz.  
- **Otimização de memória**: Armazenamento apenas dos elementos não nulos, reduzindo o uso de memória.  

---

## 📂 **Estrutura do Projeto**  
O projeto está organizado da seguinte forma:  

/SparseMatrix
│
├── /include              # Arquivos de cabeçalho (headers)
│   ├── Node.h            # Definição da classe Node (nó da matriz)
│   └── SparseMatrix.h    # Definição da classe SparseMatrix (matriz esparsa)
│
├── /src                  # Código-fonte da implementação em C++
│   ├── main.cpp          # Exemplo de uso e testes
│   └── SparseMatrix.cpp  # Implementação da classe SparseMatrix
│
├── /tests                # Arquivos de teste para a matriz esparsa
│   ├── matrix3x3.txt     # Exemplo de matriz 3x3
│   └── matrix4x4.txt     # Exemplo de matriz 4x4
│
├── clang-format.txt      # Configuração do formatação de código (clang-format)
├── .gitignore            # Arquivo para ignorar arquivos no Git
├── LICENSE               # Licença do projeto
├── Makefile              # Arquivo Makefile para compilação automatizada
├── Projeto01.pdf         # Relatório técnico do projeto
└── README.md             # Este arquivo

👥 Equipe
Este projeto foi desenvolvido por:

*Murilo Fragoso

*Carlos Daniel Rodrigues de Oliveira

Ambos os programadores participaram ativamente em todas as etapas do desenvolvimento deste trabalho, contribuindo de maneira equilibrada e colaborativa. Desde a implementação da estrutura de dados até a otimização das operações, ambos estiveram envolvidos na concepção e refinamento do código, garantindo eficiência e clareza na solução proposta. Além disso, participaram conjuntamente do planejamento, adaptação e organização do projeto, tomando decisões estratégicas para sua estruturação. No que diz respeito à documentação, ambos trabalharam na elaboração do relatório final, garantindo que a descrição do trabalho refletisse com precisão os processos e escolhas realizadas ao longo do desenvolvimento.


🙏 Agradecimentos
Gostaríamos de expressar nossa gratidão ao professor Atílio Gomes Luiz pela orientação e pelo apoio durante o desenvolvimento deste trabalho. Sua expertise e dedicação foram fundamentais para o sucesso do projeto.

#include "paleta.h"
#include <fstream>
#include <iostream>

// Construtor
Paleta::Paleta() {
    quantidade = 0;
    for (int i = 0; i < 100; ++i) {
        valores[i] = 0.0f;
        cores[i] = Cor(0, 0, 0);  // usa o construtor Cor(int, int, int)
    }
}

bool Paleta::lerDeArquivo(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo) {
        std::cerr << "Erro: não foi possível abrir o arquivo " << nomeArquivo << '\n';
        return false;
    }

    arquivo >> quantidade;

    if (quantidade <= 0 || quantidade > 100) {
        std::cerr << "Erro: quantidade inválida de cores (" << quantidade << ").\n";
        quantidade = 0;
        return false;
    }

    for (int i = 0; i < quantidade; ++i) {
        int r, g, b;
        float v;
        if (!(arquivo >> v >> r >> g >> b)) {
            std::cerr << "Erro ao ler dados da cor na linha " << i + 2 << '\n';
            quantidade = i;
            return false;
        }

        valores[i] = v;
        cores[i] = Cor{r, g, b};
    }

    return true;
}

Cor Paleta::consultarCor(float valor) const {
    if (quantidade == 0) return Cor{0, 0, 0};

    if (valor < valores[0])
        return cores[0];

    for (int i = 0; i < quantidade - 1; ++i) {
        if (valor < valores[i + 1])
            return cores[i];
    }

    return cores[quantidade - 1];
}

void imprimirCor(const Cor& cor) {
    std::cout << "RGB("
              << cor.R << ", " 
              << cor.G << ", "
              << cor.B << ")";
}
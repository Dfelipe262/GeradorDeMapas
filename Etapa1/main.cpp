#include "paleta.h"
#include <iostream>

int main() {
    Paleta p;
    if (!p.lerDeArquivo("paleta_teste.txt")) {
        std::cout << "Erro na leitura do arquivo.\n";
        return 1;
    }

    std::cout << "Digite o valor que deseja verificar:\n";
    double val;
    std::cin >> val;

    Cor cor = p.consultarCor(val);
    std::cout << "Cor correspondente: ";
    imprimirCor(cor);
    std::cout << std::endl;

    return 0;
}


#ifndef PALETA_H
#define PALETA_H

#include "cor.h"
#include <array>
#include <string>

class Paleta {
private:
    int quantidade;
    std::array<Cor, 100> cores;
    std::array<float, 100> valores;

public:
    Paleta(); // Construtor padrão
    Paleta(int qtd, const std::array<Cor, 100>& c, const std::array<float, 100>& v); // Com parâmetros
    bool lerDeArquivo(const std::string& nomeArquivo);
    Cor consultarCor(float valor) const;
};

#endif

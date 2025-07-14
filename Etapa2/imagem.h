#ifndef IMAGEM_H
#define IMAGEM_H

#include "../Etapa1/cor.h"

class Imagem {
private:
    int largura;
    int altura;
    Cor* pixels; // array linear: altura × largura

public:
    Imagem(int l, int a);      // Construtor
    ~Imagem();                 // Destrutor

    Cor getPixel(int x, int y) const;
    void setPixel(int x, int y, const Cor& cor);
    void salvarComoPPM(const std::string& nomeArquivo) const;
};

#endif

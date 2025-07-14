#include "imagem.h"
#include <fstream>

Imagem::Imagem(int l, int a) : largura(l), altura(a) {
    pixels = new Cor[largura * altura];
    for (int i = 0; i < largura * altura; ++i) {
        pixels[i] = Cor{0, 0, 0}; // inicializa tudo com preto
    }
}

Imagem::~Imagem() {
    delete[] pixels;
}

Cor Imagem::getPixel(int x, int y) const {
    return pixels[y * largura + x];
}

void Imagem::setPixel(int x, int y, const Cor& cor) {
    pixels[y * largura + x] = cor;
}

void Imagem::salvarComoPPM(const std::string& nomeArquivo) const {
    std::ofstream arquivo(nomeArquivo);
    arquivo << "P3\n";
    arquivo << largura << " " << altura << "\n";
    arquivo << "255\n";

    for (int y = 0; y < altura; ++y) {
        for (int x = 0; x < largura; ++x) {
            Cor c = getPixel(x, y);
            arquivo << (int)c.R << " " << (int)c.G<< " " << (int)c.B << "  ";
        }
        arquivo << "\n";
    }
}

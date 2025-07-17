#include <iostream>
#include "MapaAltitudes.h"
#include "paleta.h"
#include "imagem.h"

int main() {
    // Parâmetros do terreno
    int N = 10; // Gera matriz 129x129 (2^7 + 1)
    double rugosidade = 0.6;

    // Cria o mapa de altitudes
    MapaAltitudes mapa(N, rugosidade);
    mapa.gerarTerreno();

    // Lê a paleta de cores
    Paleta paleta;
    if (!paleta.lerDeArquivo("paleta.txt")) {
        std::cerr << "Erro ao carregar a paleta de cores.\n";
        return 1;
    }

    // Gera a imagem com base no mapa e na paleta
    Imagem* imagem = mapa.gerarImagem(paleta);
    if (!imagem) {
        std::cerr << "Erro ao gerar a imagem.\n";
        return 1;
    }

    // Salva a imagem em formato PPM
    imagem->salvarComoPPM("saida.ppm");
    std::cout << "Imagem gerada e salva como 'saida.ppm'\n";

    delete imagem;
    return 0;
}

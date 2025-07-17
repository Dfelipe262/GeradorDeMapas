#ifndef MAPA_ALTITUDES_HPP
#define MAPA_ALTITUDES_HPP

#include <string>
#include "imagem.h"  // ✅ <- Adicione isso
#include "paleta.h"
class MapaAltitudes {
private:
    int** matriz;
    int tamanho;
    int linhas;
    int colunas;
    double rugosidade;

    int aleatorio(double escala);
    void etapaDiamond(int lin, int col, int tam, double escala);
    void etapaSquare(int lin, int col, int tam, double escala);

public:
    MapaAltitudes(int N, double rug);
    ~MapaAltitudes();

    void gerarTerreno();
    void imprimir() const;

    int getAltura(int lin, int col) const;
    int getLinhas() const;
    int getColunas() const;

    void salvarEmArquivo(const std::string& nome) const;
    void carregarDeArquivo(const std::string& nome);
    Imagem* gerarImagem(const Paleta& paleta) const;
};

#endif


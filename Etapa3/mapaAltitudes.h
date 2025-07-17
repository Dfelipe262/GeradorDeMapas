#ifndef MAPA_ALTITUDES_H
#define MAPA_ALTITUDES_H

#include <string>
#include "../Etapa2/imagem.h" 
#include "../Etapa1/paleta.h"
class mapaAltitudes {
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
    mapaAltitudes(int N, double rug);
    ~mapaAltitudes();

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


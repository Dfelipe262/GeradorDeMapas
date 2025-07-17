#include <iostream>
#include "mapaAltitudes.h"
using namespace std;

int main() {
    int N = 3;           // Define matriz 9x9
    double rug = 0.5;    // Fator de rugosidade

    mapaAltitudes mapa(N, rug);
    mapa.gerarTerreno();

    cout << "Mapa de Altitudes Gerado:\n";
    mapa.imprimir();

    mapa.salvarEmArquivo("altitudes.txt");

    // Testar leitura
    mapaAltitudes novoMapa(1, rug);
    novoMapa.carregarDeArquivo("altitudes.txt");
    cout << "\nMapa lido do arquivo:\n";
    novoMapa.imprimir();

    return 0;
}

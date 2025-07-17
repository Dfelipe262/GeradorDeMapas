#include "mapaAltitudes.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include "../Etapa1/paleta.h"
#include "../Etapa2/imagem.h"

using namespace std;

mapaAltitudes::mapaAltitudes(int N, double rug) : rugosidade(rug) {
    tamanho = pow(2, N) + 1;
    linhas = tamanho;
    colunas = tamanho;

    matriz = new int*[linhas];
    for (int i = 0; i < linhas; ++i)
        matriz[i] = new int[colunas]{};

    srand(time(nullptr));
    matriz[0][0] = rand() % 256;
    matriz[0][tamanho - 1] = rand() % 256;
    matriz[tamanho - 1][0] = rand() % 256;
    matriz[tamanho - 1][tamanho - 1] = rand() % 256;
}

mapaAltitudes::~mapaAltitudes() {
    for (int i = 0; i < linhas; ++i)
        delete[] matriz[i];
    delete[] matriz;
}

int mapaAltitudes::aleatorio(double escala) {
    return static_cast<int>((rand() / (double)RAND_MAX) * 2 * escala - escala);
}

void mapaAltitudes::etapaDiamond(int lin, int col, int tam, double escala) {
    int meio = tam / 2;
    int media = (
        matriz[lin][col] +
        matriz[lin + tam][col] +
        matriz[lin][col + tam] +
        matriz[lin + tam][col + tam]
    ) / 4;

    matriz[lin + meio][col + meio] = media + aleatorio(escala);
}

void mapaAltitudes::etapaSquare(int lin, int col, int tam, double escala) {
    int meio = tam / 2;
    int centroLin = lin + meio;
    int centroCol = col + meio;

    if (lin >= 0)
        matriz[lin][centroCol] = (
            matriz[lin][col] +
            matriz[lin][col + tam] +
            matriz[lin + meio][col + meio]
        ) / 3 + aleatorio(escala);

    if (lin + tam < tamanho)
        matriz[lin + tam][centroCol] = (
            matriz[lin + tam][col] +
            matriz[lin + tam][col + tam] +
            matriz[lin + meio][col + meio]
        ) / 3 + aleatorio(escala);

    if (col >= 0)
        matriz[centroLin][col] = (
            matriz[lin][col] +
            matriz[lin + tam][col] +
            matriz[lin + meio][col + meio]
        ) / 3 + aleatorio(escala);

    if (col + tam < tamanho)
        matriz[centroLin][col + tam] = (
            matriz[lin][col + tam] +
            matriz[lin + tam][col + tam] +
            matriz[lin + meio][col + meio]
        ) / 3 + aleatorio(escala);
}

void mapaAltitudes::gerarTerreno() {
    int passo = tamanho - 1;
    double escala = 128.0;

    while (passo > 1) {
        int meio = passo / 2;

        for (int i = 0; i < tamanho - 1; i += passo) {
            for (int j = 0; j < tamanho - 1; j += passo) {
                etapaDiamond(i, j, passo, escala);
            }
        }

        for (int i = 0; i < tamanho - 1; i += passo) {
            for (int j = 0; j < tamanho - 1; j += passo) {
                etapaSquare(i, j, passo, escala);
            }
        }

        passo /= 2;
        escala *= rugosidade;
    }
}

void mapaAltitudes::imprimir() const {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            cout << setw(4) << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

int mapaAltitudes::getAltura(int lin, int col) const {
    return matriz[lin][col];
}

int mapaAltitudes::getLinhas() const {
    return linhas;
}

int mapaAltitudes::getColunas() const {
    return colunas;
}

void mapaAltitudes::salvarEmArquivo(const string& nome) const {
    ofstream arq(nome);
    if (!arq) {
        cerr << "Erro ao abrir o arquivo para escrita.\n";
        return;
    }

    arq << linhas << " " << colunas << "\n";
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            arq << matriz[i][j] << (j == colunas - 1 ? "" : " ");
        }
        arq << "\n";
    }

    arq.close();
}

void mapaAltitudes::carregarDeArquivo(const string& nome) {
    ifstream arq(nome);
    if (!arq) {
        cerr << "Erro ao abrir o arquivo para leitura.\n";
        return;
    }

    int novasLinhas, novasColunas;
    arq >> novasLinhas >> novasColunas;

    for (int i = 0; i < linhas; ++i) delete[] matriz[i];
    delete[] matriz;

    linhas = novasLinhas;
    colunas = novasColunas;
    tamanho = linhas;

    matriz = new int*[linhas];
    for (int i = 0; i < linhas; ++i)
        matriz[i] = new int[colunas];

    for (int i = 0; i < linhas; ++i)
        for (int j = 0; j < colunas; ++j)
            arq >> matriz[i][j];

    arq.close();
}

// etapa 4
Imagem* mapaAltitudes::gerarImagem(const Paleta& paleta) const {
    Imagem* img = new Imagem(colunas, linhas);

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            int altura = matriz[i][j];
            Cor cor = paleta.consultarCor(altura);

            // Lógica de Sombreamento
            if (i > 0 && j > 0 && altura < matriz[i - 1][j - 1]) {
                cor.R *= 0.5;
                cor.G *= 0.5;
                cor.B *= 0.5;
            }

            img->setPixel(j, i, cor);
        }
    }

    return img;
}

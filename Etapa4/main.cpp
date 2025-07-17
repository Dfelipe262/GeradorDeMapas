#include <iostream>
#include <string>
#include "../Etapa3/mapaAltitudes.h"
#include "../Etapa1/paleta.h"
#include "../Etapa2/imagem.h"

int main() {
    // Variáveis para armazenar a entrada do usuário
    std::string arquivoPaleta;
    std::string arquivoSaida;
    int N;
    double rugosidade;

    // --- Solicita os dados ao usuário ---

    // Requisito: Pedir o nome do arquivo da paleta de cores [cite: 206]
    std::cout << "Digite o nome do arquivo da paleta de cores (ex: Etapa4/paleta.txt): ";
    std::cin >> arquivoPaleta;

    // Requisito: Pedir o valor de N para o tamanho do mapa [cite: 207, 208]
    std::cout << "Digite o valor de N para gerar o mapa (ex: 10 para 1025x1025): ";
    std::cin >> N;

    // A rugosidade é um parâmetro essencial para gerar o terreno [cite: 70]
    std::cout << "Digite o fator de rugosidade (ex: 0.6): ";
    std::cin >> rugosidade;

    // Requisito: Pedir o nome do arquivo da imagem PPM a ser salvo [cite: 209]
    std::cout << "Digite o nome do arquivo de saida (ex: saida.ppm): ";
    std::cin >> arquivoSaida;

    std::cout << "\nProcessando... Por favor, aguarde.\n";

    // Cria o mapa de altitudes com os parâmetros fornecidos
    mapaAltitudes mapa(N, rugosidade);
    mapa.gerarTerreno();

    // Lê a paleta de cores do arquivo especificado
    Paleta paleta;
    if (!paleta.lerDeArquivo(arquivoPaleta)) {
        std::cerr << "Erro ao carregar a paleta de cores.\n";
        return 1;
    }

    // Gera a imagem com base no mapa e na paleta
    Imagem* imagem = mapa.gerarImagem(paleta);
    if (!imagem) {
        std::cerr << "Erro ao gerar a imagem.\n";
        return 1;
    }

    // Salva a imagem em formato PPM com o nome especificado
    imagem->salvarComoPPM(arquivoSaida);
    std::cout << "Imagem gerada com sucesso e salva como '" << arquivoSaida << "'\n";

    // Libera a memória alocada para a imagem
    delete imagem;
    return 0;
}

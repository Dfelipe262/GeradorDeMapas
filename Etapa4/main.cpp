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

    // Solicita ao usuário o nome do arquivo da paleta de cores
    std::cout << "Digite o nome do arquivo da paleta de cores (ex: Etapa4/paleta.txt): ";
    std::cin >> arquivoPaleta;

    // Solicita o valor de N, que define o tamanho do mapa (2^N + 1)
    std::cout << "Digite o valor de N para gerar o mapa (ex: 10 para 1025x1025): ";
    std::cin >> N;

    // Solicita o fator de rugosidade usado no algoritmo Diamond-Square
    std::cout << "Digite o fator de rugosidade (ex: 0.6): ";
    std::cin >> rugosidade;

    // Solicita o nome do arquivo de saída da imagem gerada
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
    
    // Verifica se a imagem foi gerada com sucesso
    if (!imagem) {
        std::cerr << "Erro ao gerar a imagem.\n";
        return 1;
    }

    // Usa o operador '->' para acessar o método do objeto apontado por 'imagem'
    imagem->salvarComoPPM(arquivoSaida);

    // Informa que a imagem foi salva com sucesso
    std::cout << "Imagem gerada com sucesso e salva como '" << arquivoSaida << "'\n";

    // Libera a memória alocada para a imagem
    delete imagem;

    return 0;
}

#include "mapaAltitudes.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include "../Etapa1/paleta.h"
#include "../Etapa2/imagem.h"

/**Constrói um mapa de altitudes usando o tamanho apropriado para o algoritmo Diamond-Square.
 * Inicializa a matriz com dimensões (2^N + 1) x (2^N + 1), define a rugosidade e os valores iniciais nos cantos extremos.
 * @param N O numero que elevado a dois e somado um retorna um valor funcional para o diamond square
 * @param rug recebe o valor de rugosidade
 */
mapaAltitudes::mapaAltitudes(int N, double rug) : rugosidade(rug) {
    tamanho = std::pow(2, N) + 1; //deixa no padrão que o diamond square funciona 2^n+1
    linhas = tamanho;
    colunas = tamanho;

    matriz = new int*[linhas];
    for (int i = 0; i < linhas; ++i)
        matriz[i] = new int[colunas]{};

    std::srand(std::time(nullptr));
    matriz[0][0] = std::rand() % 256;
    matriz[0][tamanho - 1] = std::rand() % 256;
    matriz[tamanho - 1][0] = std::rand() % 256;
    matriz[tamanho - 1][tamanho - 1] = std::rand() % 256;
}
//destrutor
mapaAltitudes::~mapaAltitudes() {
    for (int i = 0; i < linhas; ++i)
        delete[] matriz[i];
    delete[] matriz;
}
/**Gera um número inteiro aleatório no intervalo [-escala, +escala).
 * Esse valor é usado para adicionar variações (ruído) durante a geração do terreno
 * no algoritmo Diamond-Square.
 * @param escala Valor máximo da variação aleatória. O resultado será um valor entre -escala e +escala.
 * @return Um número inteiro aleatório dentro do intervalo especificado.
 */
int mapaAltitudes::aleatorio(double escala) {
    return static_cast<int>((std::rand() / static_cast<double>(RAND_MAX)) * 2 * escala - escala);
}


/**Executa a etapa "Diamond" do algoritmo Diamond-Square.
 * Calcula o valor do ponto central de um quadrado, com base na média dos seus quatro cantos
 * e adiciona uma variação aleatória proporcional a escala.
 * @param lin Linha do canto superior esquerdo do quadrado.
 * @param col Coluna do canto superior esquerdo do quadrado.
 * @param tam Tamanho do lado do quadrado (deve ser potência de 2).
 * @param escala Escala de variação usada para gerar ruído aleatório (0 a 255).
 */
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
/**Etapa "Square" do algoritmo Diamond-Square.
 * Esta função calcula os valores dos pontos localizados no meio de cada lado de um quadrado.
 * Ela usa a média de três vizinhos para definir o valor de cada ponto, e adiciona uma
 * variação aleatória proporcional à escala.
 * @param lin Linha do canto superior esquerdo do quadrado.
 * @param col Coluna do canto superior esquerdo do quadrado.
 * @param tam Tamanho do lado do quadrado.
 * @param escala Valor máximo de variação aleatória aplicada.
 */
void mapaAltitudes::etapaSquare(int lin, int col, int tam, double escala) {
    int meio = tam / 2;
    int centroLin = lin + meio;
    int centroCol = col + meio;

    if (lin >= 0) //aresta superior
        matriz[lin][centroCol] = (
            matriz[lin][col] +
            matriz[lin][col + tam] +
            matriz[lin + meio][col + meio]
        ) / 3 + aleatorio(escala);

    if (lin + tam < tamanho) //aresta inferior    para não passar do ultimo indice da matriz nas linhas
        matriz[lin + tam][centroCol] = (
            matriz[lin + tam][col] +
            matriz[lin + tam][col + tam] +
            matriz[lin + meio][col + meio]
        ) / 3 + aleatorio(escala);

    if (col >= 0) // aresta esquerda
        matriz[centroLin][col] = (
            matriz[lin][col] +
            matriz[lin + tam][col] +
            matriz[lin + meio][col + meio]
        ) / 3 + aleatorio(escala);

    if (col + tam < tamanho) // aresta da direita  para não acabar passando do ultimo indice da matriz nas colunas
        matriz[centroLin][col + tam] = (
            matriz[lin][col + tam] +
            matriz[lin + tam][col + tam] +
            matriz[lin + meio][col + meio]
        ) / 3 + aleatorio(escala);
}
/**Etapa "Square" do algoritmo Diamond-Square.
 * Esta função calcula os valores dos pontos localizados no meio de cada lado de um quadrado.
 * Ela usa a média de três vizinhos para definir o valor de cada ponto, e adiciona uma
 * variação aleatória proporcional à escala.
 
 */
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
/**Essa função imprime o mapa de altitudes (matriz) 
 * 
*/
void mapaAltitudes::imprimir() const {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            std::cout << std::setw(4) << matriz[i][j] << " "; //setw é para deixar os numeros da matriz bem alinhanhados visualmente
        }
        std::cout << std::endl;
    }
}
/**Essa função serve para pegar a altura (valor de um indice da matriz) 
 * @param lin Recebe o indice da linha que deseja saber a altura
 * @param col Recebe o indice da coluna que deseja saber a altrua
 * @return o valor da altura (o valor do indice[lin][col])
*/
int mapaAltitudes::getAltura(int lin, int col) const {
    return matriz[lin][col];
}
// Retorna o número total de linhas da matriz de altitudes.
// Também é um método 'const', ou seja, apenas leitura sem alterações na classe.
int mapaAltitudes::getLinhas() const {
    return linhas;
}

// Retorna o número total de colunas da matriz de altitudes.
// Também é um método 'const', ou seja, apenas leitura sem alterações na classe.
int mapaAltitudes::getColunas() const {
    return colunas;
}
/**Salva os dados do mapa de altitudes em um arquivo no formato ppm 
 * @param nome Recebe uma string com o nome do arquivo
*/
void mapaAltitudes::salvarEmArquivo(const std::string& nome) const {
    std::ofstream arq(nome);
    if (!arq) {
        std::cerr << "Erro ao abrir o arquivo para escrita.\n";
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
/**Carrega a matriz de altitudes a partir de um arquivo.
 * Esse método abre um arquivo de texto contendo uma matriz de inteiros.
 * Antes de carregar os novos dados, a matriz atual é desalocada da memória.
 * @param nome Nome do arquivo de onde os dados serão lidos.
 */
void mapaAltitudes::carregarDeArquivo(const std::string& nome) {
    std::ifstream arq(nome);
    if (!arq) {
        std::cerr << "Erro ao abrir o arquivo para leitura.\n";
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

//etapa 4
/**Gera uma imagem colorida a partir da matriz de altitudes.
 * Para cada ponto da matriz, é atribuída uma cor correspondente usando uma paleta.
 * Também aplica um sombreamento simples para destacar relevo:
 * se a altitude for menor que o valor da diagonal superior esquerda, a cor é escurecida.
 * @param paleta Referência para o objeto Paleta que mapeia altitudes para cores.
 * @return Ponteiro para a imagem gerada (objeto dinâmico do tipo Imagem).
 * A imagem gerada deve ser desalocada manualmente fora da função para evitar vazamentos de memória.
 */
Imagem* mapaAltitudes::gerarImagem(const Paleta& paleta) const {
    Imagem* img = new Imagem(colunas, linhas);

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            int altura = matriz[i][j];
            Cor cor = paleta.consultarCor(altura);

            // lógica do sombreamento
            if (i > 0 && j > 0 && altura < matriz[i - 1][j - 1]) {
                cor.R *= 0.5;
                cor.G *= 0.5;
                cor.B *= 0.5;
            }

            img->setPixel(j, i, cor);  //define a cor do pixel nar coordenadas j,i
        }
    }

    return img;
}

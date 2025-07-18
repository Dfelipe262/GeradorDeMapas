#include "paleta.h"
#include <fstream>
#include <iostream>

// Construtor padrão incializa com zero caso nenhum valor seja atribuído
Paleta::Paleta() {
    quantidade = 0;
    for (int i = 0; i < 100; ++i) {
        valores[i] = 0.0f;
        cores[i] = Cor(0, 0, 0);  // usa o construtor Cor(int, int, int)
    }
}
/**A função desse método é permitir uma inicialização de uma variavel do tipo paleta na sua declaração
 * @param qta A quantidade de cores a serem inicializadas.
 * @param c Um array contendo os objetos Cor (as cores em rgb).
 * @param v Um array contendo os valores de limite para cada cor.
 */
Paleta::Paleta(int qtd, const std::array<Cor, 100>& c, const std::array<float, 100>& v) {
    // Verifica se a quantidade está dentro dos limites do array
    if (qtd > 0 && qtd <= 100) {
        quantidade = qtd;
    } else {
        quantidade = 0; // Se for inválida, a paleta fica vazia
    }

    // Copia os valores e as cores dos arrays passados como parâmetro
    for (int i = 0; i < quantidade; ++i) {
        cores[i] = c[i];
        valores[i] = v[i];
    }
}
/**A função desse método é ler arquivos no formato paleta (predefinido)
 * @param nomeArquivo Ele recebe uma string (o nome do arquivo para fazer a leitura)
 * @return Ele é do tipo booleano e e quando h´um erro na leitura do arquivo ele retorna false e uma mensagem de erro
 */

bool Paleta::lerDeArquivo(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo) {
        std::cerr << "Erro: não foi possível abrir o arquivo " << nomeArquivo << '\n';
        return false;
    }

    arquivo >> quantidade;

    if (quantidade <= 0 || quantidade > 100) {
        std::cerr << "Erro: quantidade inválida de cores (" << quantidade << ").\n";
        quantidade = 0;
        return false;
    }

    for (int i = 0; i < quantidade; ++i) {
        int r, g, b;
        float v;
        if (!(arquivo >> v >> r >> g >> b)) {
            std::cerr << "Erro ao ler dados da cor na linha " << i + 2 << '\n';
            quantidade = i;
            return false;
        }

        valores[i] = v;
        cores[i] = Cor{r, g, b};
    }

    return true;
}
/**A função do método consultarCor é permitir  a verificação da cor de um determinado valor
 * @param valor É o valor correspondente a uma cor no arquivo que está sendo lido
 * @cores[] ele retorna o valor do indice de cores correspondente ao valor
 */
Cor Paleta::consultarCor(float valor) const {
    if (quantidade == 0) return Cor{0, 0, 0};

    if (valor < valores[0])
        return cores[0];

    for (int i = 0; i < quantidade - 1; ++i) {
        if (valor < valores[i + 1])
            return cores[i];
    }

    return cores[quantidade - 1];
}
/**A função imprime uma cor
 * @param cor Recebe um objeto Cor e imprime os valores no monitor
 */
void imprimirCor(const Cor& cor) {
    std::cout << "RGB("
              << cor.R << ", " 
              << cor.G << ", "
              << cor.B << ")";
}

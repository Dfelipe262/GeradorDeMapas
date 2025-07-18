#include "imagem.h"
#include <fstream>
/**Construtor padrão inicializa a matriz com zero
 * @param i a largura da imagem
 * @param a a altura da imagem
 */
Imagem::Imagem(int l, int a) : largura(l), altura(a) {
    pixels = new Cor[largura * altura];
    for (int i = 0; i < largura * altura; ++i) {
        pixels[i] = Cor{0, 0, 0}; // inicializa tudo com preto
    }
}
//destrutor
Imagem::~Imagem() {
    delete[] pixels;
}
/**Esse método retorna um pixel a partir da altura e largura
 * @param x Recebe a largura
 * @param y recebe a altura
 * @return retorna o pixel desejado
*/
Cor Imagem::getPixel(int x, int y) const {
    return pixels[y * largura + x];
}
/**Esse método configura a cor de um pixel
 * @param x Recebe a largura
 * @param y Recebe a latura
 * @param cor Recebe o objeto cor 
 */
void Imagem::setPixel(int x, int y, const Cor& cor) {
    pixels[y * largura + x] = cor;
}
/**Esse método salva os dados da imagem no formato PPM(3) 
 * @param nomeArquivo recebe uma string com o nome do arquivo onde a imagem será salva
*/
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

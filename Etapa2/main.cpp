#include "imagem.h"
#include <iostream>

int main() {
    // 🔹 Teste 1: Imagem 2x2, todos os pixels devem ser pretos (0, 0, 0)
    Imagem img1(2, 2); // quando eu inicializo o construtor todos os pixels ficam pretos
    bool todosPretos = true;

    for (int y = 0; y < 2; y++) {
        for (int x = 0; x < 2; x++) {
            Cor c = img1.getPixel(x, y);
            if (c.R != 0 || c.G != 0 || c.B != 0) {
                todosPretos = false;
            }
        }
    }

    if (todosPretos)
        std::cout << "Teste 1 OK: Todos os pixels são pretos (0, 0, 0).\n";
    else
        std::cout << "Teste 1 FALHOU: Há pixels diferentes de preto.\n";

    // 🔹 Teste 2: Imagem 3x4 toda branca (255, 255, 255)
    Imagem img2(3, 4); // inicializo a imagem
    for (int y = 0; y < 4; y++) { // deixo ela toda branca
        for (int x = 0; x < 3; x++) {
            img2.setPixel(x, y, Cor(255, 255, 255));
        }
    }

    bool todosBrancos = true;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 3; x++) {
            Cor c = img2.getPixel(x, y);
            if (c.R != 255 || c.G != 255 || c.B != 255) {
                todosBrancos = false;
            }
        }
    }

    if (todosBrancos)
        std::cout << "Teste 2 OK: Todos os pixels são brancos (255, 255, 255).\n";
    else
        std::cout << "Teste 2 FALHOU: Há pixels diferentes de branco.\n";

    // 🔹 Teste 3: Salvar a imagem branca para um arquivo PPM
    img2.salvarComoPPM("imagem_branca.ppm");
    std::cout << "Teste 3: Imagem salva como 'imagem_branca.ppm'. Abra com um visualizador para conferir.\n";

    return 0;
}

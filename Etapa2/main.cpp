#include "imagem.h"
#include <iostream>

int main() {
    
    //inicializa uma imagem toda preta
    Imagem img1(2, 2); 
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
        std::cout << "(PASSOU) Teste 1: Todos os pixels são pretos (0, 0, 0).\n";
    else
        std::cout << "(FALHA) Teste 1: Há pixels diferentes de preto.\n";

    //inicializa uma imagem toda branca
    Imagem img2(3, 4); 
    for (int y = 0; y < 4; y++) { 
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
        std::cout << "(PASSOU) Teste 2: Todos os pixels são brancos (255, 255, 255).\n";
    else
        std::cout << "(FALHA) Teste 2: Há pixels diferentes de branco.\n";

    //Salvar
    img2.salvarComoPPM("imagem_branca.ppm");
    std::cout << "Teste 2: Imagem salva como 'imagem_branca.ppm'.\n";

    return 0;
}

#ifndef COR_H
#define COR_H

#include <iostream>

struct Cor {
    int R; 
    int G; 
    int B; 

    // Construtor padrão que inicializa com preto (0,0,0)
    Cor(int r = 0, int g = 0, int b = 0) : R(r), G(g), B(b) {}
};

void imprimirCor(const Cor& c);

#endif
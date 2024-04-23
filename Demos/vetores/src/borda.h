#ifndef _BORDA_H___
#define _BORDA_H___

#include "gl_canvas2d.h"
#include "Vector2.h"
#include "reta.h"

#include <vector>


class Borda{
public:
    Vector2 bordas[4];
    std::vector<Reta*> retas;
    Borda(int altura, int largura){
        bordas[0] = Vector2(10,10);
        bordas[1] = Vector2(largura-10,10);
        bordas[2] = Vector2(largura-10,altura-10);
        bordas[3] = Vector2(10,altura-10);

        retas.push_back(new Reta(bordas[0], bordas[1]));
        retas.push_back(new Reta(bordas[1], bordas[2]));
        retas.push_back(new Reta(bordas[2], bordas[3]));
        retas.push_back(new Reta(bordas[3], bordas[0]));
        int meioX = largura/2;
        int meioY = altura/2;
        int tamanho = 100;
        retas.push_back(new Reta(Vector2(meioX-tamanho, meioY), Vector2(meioX, meioY+tamanho)));
        retas.push_back(new Reta(Vector2(meioX, meioY+tamanho), Vector2(meioX+tamanho, meioY)));
        retas.push_back(new Reta(Vector2(meioX+tamanho, meioY), Vector2(meioX, meioY-tamanho)));
        retas.push_back(new Reta(Vector2(meioX, meioY-tamanho), Vector2(meioX-tamanho, meioY)));
    }

    std::vector<Reta*> getRetas(){
        return retas;
    }

    void render(bool debug){
        for(int i = 0; i < retas.size(); i++){
            retas[i]->render(debug);
        }
    }


};

#endif

#ifndef _BOLA_H___
#define _BOLA_H___

#include "gl_canvas2d.h"
#include "Vector2.h"

class Bola{
public:
    Vector2 pos;
    Vector2 dir;

    float velocidade = 0.1;

    Bola(Vector2 posInicial){
        pos = posInicial;
        dir.x = (rand()%100)/100.0;
        dir.y = (rand()%100)/100.0;
        dir.normalize();
    }

    void render(int fps){
        CV::color(0,0,1);
        CV::circleFill(pos.x, pos.y, 10, 20);
        pos = pos + (dir*velocidade);
    }

    void colidiu(Vector2 normalColisao){
        dir = d - 2*((dir.dot(normalColisao))*normalColisao)*
    }
};

#endif // _BOLA_H___

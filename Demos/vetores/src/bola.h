#ifndef _BOLA_H___
#define _BOLA_H___

#include "gl_canvas2d.h"
#include "Vector2.h"
#include "reta.h"
#include "Borda.h" // Inclua a definição da classe Borda aqui

class Bola {
public:
    Vector2 pos;
    Vector2 dir;
    float velocidade = 2;
    Borda * borda = NULL;
    int raio = 10;

    Bola(Vector2 posInicial, Borda * b) {
        pos = posInicial;
        dir.x = (rand() % 200)-100;
        dir.y = (rand() % 200)-100;
        dir.normalize();
        borda = b;

    }

    void renderDir() {
        CV::color(0, 1.0, 0);
        CV::line(pos.x, pos.y, pos.x + (dir.x * 15), pos.y + (dir.y * 15)); // Correção da linha
    }


    void render(int fps, bool debug) {
        CV::color(0, 0, 1);
        CV::circleFill(pos.x, pos.y, raio, 20);
        pos = pos + (dir * velocidade);
        checaColisao();
        if(debug){
            renderDir();
        }

    }

    void checaColisao() {
        std::vector<Reta*> retas = borda->getRetas();
        for (Reta* reta : retas) {
            if(reta->colisaoCirculo(pos, raio)){
                colidiu(reta->normal);
            }
        }
    }

    void colidiu(Vector2 normalColisao) {
        normalColisao.normalize();
        float aux = dir.dot(normalColisao);
        Vector2 v = normalColisao * aux;
        v = v * 2;
        dir = dir - v;
    }
};

#endif // _BOLA_H___

#ifndef __RETA_2_H__
#define __RETA_2_H__

#include <vector>
#include "Vector2.h" // Suponha que Vector2 seja uma classe adequada para manipulação de vetores 2D

class Reta {
public:
    std::vector<Vector2> pontos;
    Vector2 normal;

    Reta(const Vector2& inicio, const Vector2& fim) {
        calculatePoints(inicio, fim);
        calculateNormal();
    }

    void calculatePoints(const Vector2& inicio, const Vector2& fim) {
        pontos.clear();

        pontos.push_back(inicio);

        Vector2 direcao = fim - inicio;
        float comprimento = direcao.magnitude();

        float passo = 5.0f;
        direcao.normalize();

        for (float d = passo; d < comprimento; d += passo) {
            Vector2 novoPonto = inicio + direcao * d;
            pontos.push_back(novoPonto);
        }

        pontos.push_back(fim);
    }

    void calculateNormal() {
        if (pontos.size() >= 2) {
            Vector2 direcao = pontos[1] - pontos[0];
            normal.set(-direcao.y, direcao.x);
            normal.normalize();
        }
    }

    bool colisaoCirculo(Vector2 centroCirculo, float raio) const {
        for (const auto& ponto : pontos) {
            // Calcula a distância entre o ponto da reta e o centro do círculo
            float dist = ponto.distance(centroCirculo);
            if (dist <= raio) {
                return true; // Colisão detectada
            }
        }
        return false; // Sem colisão
    }

    void render(bool debug) const {
        if (pontos.size() >= 2) {
            CV::color(1, 0, 0);
            for (int i = 0; i < pontos.size() - 1; ++i) {
                //CV::circleFill(pontos[i].x, pontos[i].y, 5, 10);
                CV::line(pontos[i].x, pontos[i].y, pontos[i + 1].x, pontos[i + 1].y);

            }
            if(debug){
                Vector2 meio = (pontos[0] + pontos[pontos.size()-1]) * 0.5f;
                Vector2 normalDirection = meio + normal * 20.0f;
                CV::color(0, 1.0, 0);
                CV::line(meio.x, meio.y, normalDirection.x, normalDirection.y);
            }
        }
    }
};

#endif

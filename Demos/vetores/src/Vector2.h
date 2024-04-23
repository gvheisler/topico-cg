#ifndef __VECTOR_2_H__
#define __VECTOR_2_H__

#include <cmath> // Para usar funções matemáticas como sqrt()

class Vector2
{
public:
    float x, y;

    Vector2()
    {
        x = y = 0;
    }

    Vector2(float _x, float _y)
    {
        x = _x;
        y = _y;
    }

    void set(float _x, float _y)
    {
        x = _x;
        y = _y;
    }

    void normalize()
    {
        float norm = sqrt(x * x + y * y);

        if (norm == 0.0)
        {
            printf("\n\nNormalize::Divisao por zero");
            x = 1;
            y = 1;
            return;
        }
        x /= norm;
        y /= norm;
    }

    float magnitude() const
    {
        return sqrt(x * x + y * y);
    }

    float dot(const Vector2 &v2) const
    {
        return (x * v2.x) + (y * v2.y);
    }

    float distance(const Vector2 &v2) const
    {
        float dx = x - v2.x;
        float dy = y - v2.y;
        return sqrt(dx * dx + dy * dy);
    }

    Vector2 operator-(const Vector2 &v) const
    {
        Vector2 aux(x - v.x, y - v.y);
        return aux;
    }

    Vector2 operator+(const Vector2 &v) const
    {
        Vector2 aux(x + v.x, y + v.y);
        return aux;
    }

    Vector2 operator*(const float &a) const
    {
        Vector2 aux(x * a, y * a);
        return aux;
    }

    // Adicione outros overloads de operadores conforme necessário...

};

#endif

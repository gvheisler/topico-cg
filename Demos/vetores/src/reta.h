#ifndef _RETA_H___
#define _RETA_H___

#include "gl_canvas2d.h"
#include "Vector2.h"

class Reta{
public:
    Vector2 pos[2];
    Reta(int x1, int y1, int x2, int y2){
        pos[0].x = x1;
        pos[0].y = y1;
        pos[1].x = x2;
        pos[1].y = y2;
    }
    Reta(Vector2 p1, Vector2 p2){
        pos[0] = p1;
        pos[1] = p2;
    }

    void render(){
        CV::color(1,0,0);
        CV::line(pos[0].x, pos[0].y, pos[1].x, pos[1].y);
    }

};

#endif

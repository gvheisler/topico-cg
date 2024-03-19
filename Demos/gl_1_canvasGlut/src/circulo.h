#ifndef _circulo_h_
#define _circulo_h_

class Circulo{
public:
    int x, y, raio;

    Circulo(int x_, int y_, int raio_){
        x = x_;
        y = y_;
        raio = raio_;
    }

    void render(){
        CV::color(1,0,0);
        CV::circleFill(x, y, raio, 100);
    }



};


#endif // _circulo_h_

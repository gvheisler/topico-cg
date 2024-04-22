
#include "Bmp.h"

class Imagem{
public:
    int x, y;
    Bmp * bmp;
    unsigned char * data;
    Imagem(char * path, int x, int y){
        this->x = x;
        this->y = y;
        bmp = new Bmp(path);
        bmp->convertBGRtoRGB();
        data = bmp->getImage();
    }

    void render(int offsetx, int offsety){
        for(int i = 0; i<bmp->getHeight(); i++){
            for(int j = 0; j<bmp->getWidth(); j++){
                int idx = (i*bmp->getWidth()*3)+(j*3);
                CV::color((float(data[idx])/255.0), (float(data[idx+1])/255.0), (float(data[idx+2])/255.0));
                CV::rectFill(offsetx+i,offsety+j,offsetx+i+1,offsety+j+1);
            }
        }
    }


};

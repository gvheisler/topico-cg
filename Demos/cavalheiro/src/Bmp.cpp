//*********************************************************
//
// classe para fazer o carregamento de arquivos no formato BMP
// Autor: Cesar Tadeu Pozzer
//        pozzer@inf.ufsm.br
//  Versao 09/2010
//
//**********************************************************

#include "Bmp.h"
#include <string.h>
#include "gl_canvas2d.h"

Bmp::Bmp(const char *fileName)
{
   width = height = 0;
   data = NULL;
   if( fileName != NULL && strlen(fileName) > 0 )
   {
      load(fileName);
   }
   else
   {
      printf("Error: Invalid BMP filename");
   }
}

Bmp::~Bmp() {

    if (data != nullptr) {
        delete[] data;
        data = nullptr;
    }
}

uchar* Bmp::getImage()
{
  return data;
}

int Bmp::getWidth(void)
{
  return width;
}

int Bmp::getHeight(void)
{
  return height;
}

void Bmp::convertBGRtoRGB()
{
  unsigned char tmp;
  if( data != NULL )
  {
     for(int y=0; y<height; y++)
     for(int x=0; x<width*3; x+=3)
     {
        int pos = y*bytesPerLine + x;
        tmp = data[pos];
        data[pos] = data[pos+2];
        data[pos+2] = tmp;
     }
  }
}


void Bmp::load(const char *fileName)
{
  FILE *fp = fopen(fileName, "rb");
  if( fp == NULL )
  {
     printf("\nErro ao abrir arquivo %s para leitura", fileName);
     return;
  }

  printf("\n\nCarregando arquivo %s", fileName);

  //le o HEADER componente a componente devido ao problema de alinhamento de bytes. Usando
  //o comando fread(header, sizeof(HEADER),1,fp) sao lidos 16 bytes ao inves de 14
  fread(&header.type,      sizeof(unsigned short int), 1, fp);
  fread(&header.size,      sizeof(unsigned int),       1, fp);
  fread(&header.reserved1, sizeof(unsigned short int), 1, fp);
  fread(&header.reserved2, sizeof(unsigned short int), 1, fp);
  fread(&header.offset,    sizeof(unsigned int),       1, fp); //indica inicio do bloco de pixels

  //le o INFOHEADER componente a componente devido ao problema de alinhamento de bytes
  fread(&info.size,        sizeof(unsigned int),       1, fp);
  fread(&info.width,       sizeof(int),                1, fp);
  fread(&info.height,      sizeof(int),                1, fp);
  fread(&info.planes,      sizeof(unsigned short int), 1, fp);
  fread(&info.bits,        sizeof(unsigned short int), 1, fp);
  fread(&info.compression, sizeof(unsigned int),       1, fp);
  fread(&info.imagesize,   sizeof(unsigned int),       1, fp);
  fread(&info.xresolution, sizeof(int),                1, fp);
  fread(&info.yresolution, sizeof(int),                1, fp);
  fread(&info.ncolours,    sizeof(unsigned int),       1, fp);
  fread(&info.impcolours,  sizeof(unsigned int),       1, fp);

  width  = info.width;
  height = info.height;
  bits   = info.bits;
  bytesPerLine =(3 * (width + 1) / 4) * 4;
  imagesize    = bytesPerLine*height;
  int delta    = bytesPerLine - (3 * width);

  printf("\nImagem: %dx%d - Bits: %d", width, height, bits);
  printf("\nbytesPerLine: %d", bytesPerLine);
  printf("\nbytesPerLine: %d", width * 3);
  printf("\ndelta: %d", delta);
  printf("\nimagesize: %d %d", imagesize, info.imagesize);

  //realiza diversas verificacoes de erro e compatibilidade
  if( header.type != 19778 )
  {
     printf("\nError: Arquivo BMP invalido");
     getchar();
     exit(0);
  }

  if( width*height*3 != imagesize )
  {
     printf("\nWarning: Arquivo BMP nao tem largura multipla de 4");
     getchar();
  }

  if( info.compression != 0 )
  {
     printf("\nError: Formato BMP comprimido nao suportado");
     getchar();
     return;
  }
  if( bits != 24 )
  {
     printf("\nError: Formato BMP com %d bits/pixel nao suportado", bits);
     getchar();
     return;
  }

  if( info.planes != 1 )
  {
     printf("\nError: Numero de Planes nao suportado: %d", info.planes);
     getchar();
     return;
  }

  data = new unsigned char[imagesize];
  fseek(fp, header.offset, SEEK_SET);
  fread(data, sizeof(unsigned char), imagesize, fp);
    processaCores();

  fclose(fp);
}

void Bmp::processaCores() {

    convertBGRtoRGB();
    unsigned char *data;
    data = getImage();
    int width = getWidth();
    int height = getHeight();

    if (data != NULL) {

        if (matrizCores != NULL) {
            for (int i = 0; i < height; i++) {
                delete[] matrizCores[i];
            }
            delete[] matrizCores;
        }

        matrizCores = new CorRGB*[height];

        for (int i = 0; i < height; i++) {
            matrizCores[i] = new CorRGB[width];
        }

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int pos = (y * width + x) * 3;
                matrizCores[y][x].r = data[pos];
                matrizCores[y][x].g = data[pos + 1];
                matrizCores[y][x].b = data[pos + 2];
            }
        }

        criaHistograma(matrizCores,width,height,histogramaRed,RED);
        criaHistograma(matrizCores,width,height,histogramaBlue,BLUE);
        criaHistograma(matrizCores,width,height,histogramaGreen,GREEN);
        criaHistograma(matrizCores,width,height,histogramaGray,GRAY);
    }


}

void Bmp::criaHistograma(CorRGB** matrizCores, int width, int height, std::vector<int>& histograma, CanalCor canal) {
    // Inicializa o histograma com zeros
    histograma.assign(256, 0);

    // Percorre todos os pixels da imagem
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Obtém o valor do canal de cor do pixel, dependendo do parâmetro de cor
            unsigned char cor;
            switch(canal) {
                case RED:
                    cor = matrizCores[y][x].r;
                    break;
                case GREEN:
                    cor = matrizCores[y][x].g;
                    break;
                case BLUE:
                    cor = matrizCores[y][x].b;
                    break;
                case GRAY: {
                    int r = matrizCores[y][x].r;
                    int g = matrizCores[y][x].g;
                    int b = matrizCores[y][x].b;
                    // Caso seja desejado o histograma em escala de cinza, pode-se calcular a média dos valores RGB
                    cor = (0.3f*r + 0.59f*g + 0.11f*b);
                    break;
                }
                default:
                    // Trata caso inválido
                    break;
            }

            // Incrementa a contagem do valor da intensidade de cor no histograma
            histograma[cor]++;
        }
    }
}


void Bmp::desenhaHistograma(const std::vector<int>& histograma, CanalCor canal, int startX, int startY) {
    // Calcula a escala vertical do histograma para caber na altura fornecida
    CV::clear(1,1,1);
    int histogramWidth = 180; // Largura do histograma
    int histogramHeight = 100; // Altura do histograma
    int proporcaoEscala = 10;
    int offset_escala_y = 40;
    int offset_escala_x = 10;

    int maxContagem = *std::max_element(histograma.begin(), histograma.end());
    float escalaVertical = static_cast<float>(histogramHeight) / maxContagem;
    float escalaHorizontal = static_cast<float>(histogramWidth) / histograma.size();

    // Define a cor do histograma de acordo com o canal
    switch(canal) {
        case RED:
            CV::color(1.0f, 0.0f, 0.0f); // Vermelho
            break;
        case GREEN:
            CV::color(0.0f, 1.0f, 0.0f); // Verde
            break;
        case BLUE:
            CV::color(0.0f, 0.0f, 1.0f); // Azul
            break;
        case GRAY:
            CV::color(0.5f, 0.5f, 0.5f); // Cinza
            break;
        default:
            // Trata caso inválido
            break;
    }

    // Desenha o eixo X do histograma
    CV::line(startX, startY, startX + histogramWidth, startY);

    // Desenha o eixo Y do histograma
    CV::line(startX, startY - histogramHeight, startX, startY);

    // Desenha a escala numérica ao longo do eixo Y
    for (int i = 0; i <= proporcaoEscala; i+=2) {
        int escalaY = startY - i * histogramHeight / proporcaoEscala;
        std::string scale = std::to_string(i * maxContagem / proporcaoEscala);
        CV::text(startX - offset_escala_y, escalaY, scale.c_str());
    }

    // Desenha a escala ao longo do eixo X
    CV::text(startX, startY + offset_escala_x, "0");
    CV::text(startX + histogramWidth, startY + offset_escala_x, "255(px)");

    // Desenha as barras do histograma
    for (int i = 0; i < histograma.size(); i++) {
        int barHeight = static_cast<int>(histograma[i] * escalaVertical);
        int barX = startX + i * escalaHorizontal; // Posição X da barra
        int barY = startY - barHeight; // Posição Y da barra

        CV::rectFill(barX, barY, barX + 1, startY); // Desenha a barra
    }
}


void Bmp::rotacaoVertical() {
    if (matrizCores != NULL) {
        int metadeAltura = height / 2;
        for (int y = 0; y < metadeAltura; y++) {
            // Troca as linhas y e height - y - 1
            for (int x = 0; x < width; x++) {
                CorRGB temp = matrizCores[y][x];
                matrizCores[y][x] = matrizCores[height - y - 1][x];
                matrizCores[height - y - 1][x] = temp;
            }
        }
    }
}


void Bmp::rotacaoHorizontal() {
    if (matrizCores != NULL) {
        int metadeLargura = width / 2;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < metadeLargura; x++) {
                // Troca os pixels x e width - x - 1 na linha y
                CorRGB temp = matrizCores[y][x];
                matrizCores[y][x] = matrizCores[y][width - x - 1];
                matrizCores[y][width - x - 1] = temp;
            }
        }
    }
}


void Bmp::Render(int x, int y) {
    CV::clear(1, 1, 1);

    int xStartEsquerda = 50;  // Início da exibição no canto esquerdo
    int yStart = 200;  // Altura inicial da primeira imagem
    int r, g, b;
    if (matrizCores != NULL) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                r = matrizCores[y][x].r;
                g = matrizCores[y][x].g;
                b = matrizCores[y][x].b;

                // Exibe imagem original em RGB (canto esquerdo)
                CV::color(float(r / 255.0), float(g / 255.0), float(b / 255.0));
                CV::rect(x + xStartEsquerda, height - y - 1 + yStart, x + xStartEsquerda + 1, height - y - 1 + yStart + 1);
            }
        }
    }
}

void Bmp::desenhaRGB() {
    int xStartDireita = 750;  // Início da exibição no canto direito
    int yStart = 120;  // Altura inicial da primeira imagem
    int r, g, b;
    if (matrizCores != NULL) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                r = matrizCores[y][x].r;
                g = matrizCores[y][x].g;
                b = matrizCores[y][x].b;
                unsigned char cinza = (matrizCores[y][x].r * 0.3f + matrizCores[y][x].g * 0.59f + matrizCores[y][x].b * 0.11f);

                // Define o fator de escala para as imagens no lado direito (50% do tamanho original)
                float escala = 0.5f;
                ///*
                // Calcula o deslocamento vertical entre as imagens no lado direito (10% do tamanho de uma imagem)
                int deslocamentoVertical = height * escala * 0.1;

                // Exibe imagem em canal vermelho (canto direito)
                CV::color(float(r / 255.0), 0.0f, 0.0f);
                CV::rect(x * escala + xStartDireita, (height - y - 1)*escala + yStart, x * escala + xStartDireita + 1, (height - y)*escala + yStart + 1);

                // Exibe imagem em canal verde (canto direito)
                CV::color(0.0f, float(g / 255.0), 0.0f);
                CV::rect(x * escala + xStartDireita, (height - y - 1) * escala + yStart + deslocamentoVertical+height*escala, x * escala + xStartDireita + 1, (height - y) * escala + yStart + deslocamentoVertical + 1+height*escala);

                // Exibe imagem em canal azul (canto direito)
                CV::color(0.0f, 0.0f, float(b / 255.0));
                CV::rect(x * escala + xStartDireita, (height - y - 1) * escala + yStart + deslocamentoVertical+height*escala*2+10, x * escala + xStartDireita + 1, (height - y) * escala + yStart + deslocamentoVertical + 1+height*escala*2+10);
                //CV::rect(x * escala + xStartDireita, yStart + deslocamentoVertical * 2, x * escala + xStartDireita + 1, yStart + deslocamentoVertical * 3);

                // Exibe imagem em escala de cinza (canto direito)
                CV::color(float(cinza / 255.0), float(cinza / 255.0), float(cinza / 255.0));
                CV::rect(x * escala + xStartDireita, (height - y - 1) * escala + yStart + deslocamentoVertical+height*escala*3+20, x * escala + xStartDireita + 1, (height - y) * escala + yStart + deslocamentoVertical + 1+height*escala*3+20);
                //CV::rect(x * escala + xStartDireita, yStart + deslocamentoVertical * 3, x * escala + xStartDireita + 1, yStart + deslocamentoVertical * 4);
                //*/
            }
        }
    }
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
/*void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   mouseX = x; //guarda as coordenadas do mouse para exibir dentro da render()
   mouseY = y;

   printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);

   if( state == 0 ) //clicou
   {
       if( Colidiu(x, y) )
       {
           while (state == 0)
            printf("\nClicou no quadrado\n");
       }
   }

}

  //recebe as coordenadas do mouse para tratar clique ou detectar quando o mouse esta em cima do botao
  bool Colidiu(int mx, int my)
  {
      if( mx >= x && mx <= (50 + 100) && my >= y && my <= (50 + 100) )
      {
          return true;
      }
      return false;
  }*/

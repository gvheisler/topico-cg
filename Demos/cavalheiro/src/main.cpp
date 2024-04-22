/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         05/2024
//
//  Pode ser utilizada para fazer desenhos, animacoes, e jogos simples.
//  Tem tratamento de mouse e teclado
//  Estude o OpenGL antes de tentar compreender o arquivo gl_canvas.cpp
//
//  Versao 2.0
//
//  Instruções:
//	  Para alterar a animacao, digite numeros entre 1 e 3
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "gl_canvas2d.h"

#include "Bola.h"
#include "Relogio.h"
#include "ManagerBotoes.h"

//largura e altura inicial da tela . Alteram com o redimensionamento de tela
int screenWidth = 960, screenHeight = 720;


Bola    *b = NULL;
Relogio *r = NULL;
ManagerBotoes   *mbt = NULL; //se a aplicacao tiver varios botoes, sugiro implementar um manager de botoes.
Bmp     *bmp = NULL;
Bmp     *bmp2 = NULL;
Bmp     *bmp3 = NULL;
ImageManager *im = NULL;

int opcao  = 50;//variavel global para selecao do que sera exibido na canvas.
int mouseX, mouseY; //variaveis globais do mouse para poder exibir dentro da render().


void DrawMouseScreenCoords()
{
    char str[100];
    sprintf(str, "Mouse: (%d,%d)", mouseX, mouseY);
    CV::text(10,300, str);
    sprintf(str, "Screen: (%d,%d)", screenWidth, screenHeight);
    CV::text(10,320, str);
}


//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais
//Todos os comandos para desenho na canvas devem ser chamados dentro da render().
//Deve-se manter essa função com poucas linhas de codigo.
void render()
{
    CV::clear(1,1,1);

   mbt->renderizaBotoes();
   im->Render();
   //bmp2->Render(300,300);
   //bmp3->Render(500,500);


   /*DesenhaLinhaDegrade();

   if( opcao == 49 ) //'1' -> relogio
   {
      r->anima();
   }
   if( opcao == '2' ) //50 -> bola
   {
      b->anima();
   }
   if( opcao == 51 ) //'3' -> senoide
   {
       DesenhaSenoide();
   }*/


   //sleep(10); //nao eh controle de FPS. Somente um limitador de FPS.
}

//funcao chamada toda vez que uma tecla for pressionada.
void keyboard(int key)
{
   printf("\nTecla: %d" , key);
   if( key < 200 )
   {
      opcao = key;
   }

   switch(key)
   {
      case 27:
	     exit(0);
	  break;

	  //seta para a esquerda
      case 200:
         b->move(-10);
	  break;

	  //seta para a direita
	  case 202:
         b->move(10);
	  break;
   }
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
   printf("\nLiberou: %d" , key);
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   mouseX = x; //guarda as coordenadas do mouse para exibir dentro da render()
   mouseY = y;

   printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);

   if( state == 0 ) //clicou
   {
       /*if( bt->Colidiu(x, y) )
       {
            printf("\nClicou no botao\n");
            CV::clear(1,1,1);
            bmp->desenhaHistograma(bmp->histogramaRed,bmp->RED,300,400);
       }*/
       mbt->verificaClique(x,y);
   }
}

int main(void)
{
   im = new ImageManager(1);
   mbt = new ManagerBotoes(im);
   //bmp = new Bmp("./1_canvasGlut/images/a.bmp");
   //bmp2 = new Bmp("./1_canvasGlut/images/b.bmp");
   //bmp3 = new Bmp("./1_canvasGlut/images/c.bmp");

   CV::init(screenWidth, screenHeight, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3");
   CV::run();
}

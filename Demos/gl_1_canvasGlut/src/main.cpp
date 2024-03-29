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

#include <vector>

#include "gl_canvas2d.h"

#include "Bola.h"
#include "Relogio.h"
#include "maanager.h"
#include "circulo.h"

//largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int screenWidth = 500, screenHeight = 500;

Manager * botoes = NULL;


int mouseX, mouseY; //variaveis globais do mouse para poder exibir dentro da render().

std::vector<Circulo*> vetor = {};


void DrawMouseScreenCoords()
{
    char str[100];
    sprintf(str, "Mouse: (%d,%d)", mouseX, mouseY);
    CV::text(10,300, str);
    sprintf(str, "Screen: (%d,%d)", screenWidth, screenHeight);
    CV::text(10,320, str);
}

void render()
{
    CV::clear(0,0,0);
    CV::color(1,1,1);
    CV::text(20,500,"Programa Demo Canvas2D");
    botoes->render();
    DrawMouseScreenCoords();
    //printf("\nvetor size = %d", vetor.size());
}

//funcao chamada toda vez que uma tecla for pressionada.
void keyboard(int key)
{
   printf("\nTecla: %d" , key);

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
   botoes->clique(state, button, mouseX, mouseY);

}

void teste(){
    exit(0);
}

void printa(){
    printf("Deu certo!!!!!\n");
}

int main(void)
{
   CV::init(&screenWidth, &screenHeight, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3");
   botoes = new Manager();
   botoes->addBotao(100,100, 50, 100, "abc", teste);
   botoes->addBotao(250,300, 100, 50, "teste", printa);
   CV::run();
}

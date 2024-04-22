#include "ImageManager.h"
#include <vector>
#include <unistd.h>

ImageManager::ImageManager(int numImages)
{
    indiceImagemAtual = -1;
    imagemSelecionada = 0;
    mostrarHistogramas = false;
    mostrarRGB = false;

    std::string directory = "./1_canvasGlut/images/";
    char letter = 'a';
    std::string extension = ".bmp";

    Bmp* bmp = NULL;
    //bmp = new Bmp("./1_canvasGlut/images/a.bmp");
    bmp = new Bmp(".\\1_canvasGlut\\images\\a.bmp");
    printf("Criei o que precisava");
    images.push_back(bmp);
    /*
    for (int i = 0; i < numImages; i++) {
        std::string fileName = directory + std::string(1, letter) + extension;
        printf("\nVou criar a Bmp: %s\n",fileName.c_str());
        bmp = new Bmp(fileName.c_str());
        printf("\nVou adicionar no vetor a Bmp: %s\n",fileName.c_str());
        images.push_back(bmp);
        //delete bmp;
        letter++;
    }*/
}

ImageManager::~ImageManager()
{
    //dtor
}

void ImageManager::Render() {
    //printf("ImageManager Render, indiceImagemAtual = %d\n",indiceImagemAtual);
    if(indiceImagemAtual > -1) {
        images[indiceImagemAtual]->Render(300,300);
    }

    if(mostrarHistogramas) {

        images[indiceImagemAtual]->desenhaHistograma(images[indiceImagemAtual]->histogramaRed,images[indiceImagemAtual]->RED,700,250);
        images[indiceImagemAtual]->desenhaHistograma(images[indiceImagemAtual]->histogramaGreen,images[indiceImagemAtual]->GREEN,700,380);
        images[indiceImagemAtual]->desenhaHistograma(images[indiceImagemAtual]->histogramaBlue,images[indiceImagemAtual]->BLUE,700,510);
        images[indiceImagemAtual]->desenhaHistograma(images[indiceImagemAtual]->histogramaGray,images[indiceImagemAtual]->GRAY,700,640);
    }

    if(mostrarRGB) {
        images[indiceImagemAtual]->desenhaRGB();
    }

}

void ImageManager::carregarImagem() {
    indiceImagemAtual = 0;
    printf("\ntamanho do vetor: %d\n",images.size());
    if (indiceImagemAtual < images.size()) {

        int startX = 50;
        int startY = 200;
        for (int i = 0; i < indiceImagemAtual; i++) {
            startX += images[i]->getWidth();
        }

        //images[indiceImagemAtual]->Render(0, 0); //precisod ar um jeito de fazer ela ficar na tela
    }
}

void ImageManager::rotacaoVertical(){
    if (imagemSelecionada >= 0 && imagemSelecionada < images.size()) {
        images[indiceImagemAtual]->rotacaoVertical();

    }
}

void ImageManager::rotacaoHorizontal(){
    if (imagemSelecionada >= 0 && imagemSelecionada < images.size()) {
        images[indiceImagemAtual]->rotacaoHorizontal();

    }
}

void ImageManager::exibirHistograma() {
    if (imagemSelecionada >= 0 && imagemSelecionada < images.size()) {
        if(mostrarRGB == true) {
            mostrarRGB = false;
        }

        if(mostrarHistogramas == false) {
            mostrarHistogramas = true;
        } else {
            mostrarHistogramas = false;
        }
    }
}

void ImageManager::exibirCanaisRGB() {
    if (imagemSelecionada >= 0 && imagemSelecionada < images.size()) {
        if(mostrarHistogramas == true) {
            mostrarHistogramas = false;
        }

        if(mostrarRGB == false) {
            mostrarRGB = true;
        } else {
            mostrarRGB= false;
        }
    }
}

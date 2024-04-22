#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include "Bmp.h"

class ImageManager
{
    private:
        std::vector<Bmp*> images;
        int imagemSelecionada;
        int indiceImagemAtual;
        bool mostrarHistogramas;
        bool mostrarRGB;

    public:
        ImageManager(int numImages);
        virtual ~ImageManager();

        bool temImagemselecionada();
        void Render();

        //Métodos chamados ao clicar em Botoes
        void carregarImagem();
        void rotacaoHorizontal();
        void rotacaoVertical();
        void exibirCanaisRGB();
        void exibirHistograma();

};

#endif // IMAGEMANAGER_H

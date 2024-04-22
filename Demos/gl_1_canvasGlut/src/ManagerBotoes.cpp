#include "ManagerBotoes.h"

ManagerBotoes::ManagerBotoes(ImageManager *im)
{
    imageManager = im;
    int widthBotao = 150;
    int heightBotao = 50;
    int posY = 50;
    int startX = 50;


    // Criação dos botões e adição ao vetor
    botoes.push_back(Botao(startX, posY, widthBotao, heightBotao, "Carregar img"));
    botoes.push_back(Botao(startX + widthBotao + startX/2, posY, widthBotao, heightBotao, "Rotacao Vert."));
    botoes.push_back(Botao(startX + widthBotao*2 + startX/2*2, posY, widthBotao, heightBotao, "Rotacao Horiz."));
    botoes.push_back(Botao(startX + widthBotao*3 + startX/2*3, posY, widthBotao, heightBotao, "Canais RGB"));
    botoes.push_back(Botao(startX + widthBotao*4 + startX/2*4, posY, widthBotao, heightBotao, "Histograma"));
}

ManagerBotoes::~ManagerBotoes()
{
    //dtor
}

void ManagerBotoes::renderizaBotoes() {

    for (const auto& botao : botoes) {
        botao.Render();
    }

}

void ManagerBotoes::verificaClique(int mx, int my) {

    for (auto& botao : botoes) {
        if (botao.Colidiu(mx, my)) {
            const char* label = botao.getLabel();
            if (strcmp(label, "Carregar img") == 0) {
                imageManager->carregarImagem();

            } else if (strcmp(label, "Rotacao Vert.") == 0) {
                imageManager->rotacaoVertical();

            } else if (strcmp(label, "Rotacao Horiz.") == 0) {
                imageManager->rotacaoHorizontal();

            } else if (strcmp(label, "Canais RGB") == 0) {
                imageManager->exibirCanaisRGB();

            } else if (strcmp(label, "Histograma") == 0) {
                imageManager->exibirHistograma();

            }
        }
    }

}

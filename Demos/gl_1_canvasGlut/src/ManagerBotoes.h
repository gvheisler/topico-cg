#ifndef MANAGERBOTOES_H
#define MANAGERBOTOES_H

#include <vector>
#include "Botao.h"
#include "ImageManager.h"

class ManagerBotoes
{
    private:
        std::vector<Botao> botoes;
        ImageManager* imageManager;

    public:
        ManagerBotoes(ImageManager* im);
        virtual ~ManagerBotoes();
        void renderizaBotoes();
        void verificaClique(int mx, int my);
};

#endif // MANAGERBOTOES_H

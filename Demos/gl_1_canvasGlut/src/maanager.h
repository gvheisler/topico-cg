#ifndef _manager_h_
#define _manager_h_

#include "Botao.h"
#include <vector>

class Manager{
public:
    std::vector<Botao*> vet_botoes;
    Manager(){
        vet_botoes = {};
    }

    void addBotao(int x, int y, int larg, int altura, char * text, std::function<void()> funcao){
        vet_botoes.push_back(new Botao(x, y, larg, altura, text, funcao));
    }

    void render(){
        for(int i = 0; i<vet_botoes.size(); i++){
            vet_botoes[i]->Render();
        }
    }

    void clique(int state, int button, int mx, int my){
        for(int i = 0; i<vet_botoes.size(); i++){
            if(state == 0 && button == 0){
                if(vet_botoes[i]->Colidiu(mx, my)){
                    vet_botoes[i]->executa();
                }
            }
        }
    }


};


#endif

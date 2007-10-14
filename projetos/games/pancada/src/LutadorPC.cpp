
#include "LutadorPC.h"

LutadorPC::LutadorPC(TipoLutador tipo){
	CabecaFactory cFactory;
	cabeca = cFactory.criar(tipo);
	olharBaixo();
}

LutadorPC::~LutadorPC(){

}

void LutadorPC::acao(InputSystem * input) 
{
	int passo=3;

	//Movimentação
	if (input->teclado->isKey(SDLK_w)){
		posicao.y-=passo;
	} else if (input->teclado->isKey(SDLK_s)){
		posicao.y+=passo;
	}
    if (input->teclado->isKey(SDLK_a)){
        posicao.x-=passo;
    } else if (input->teclado->isKey(SDLK_d)){
        posicao.x+=passo;
    }
 	//Controle de Socos - Soco Esquerdo
    if (delay.tiroA<=0){
        if(input->teclado->isKey(SDLK_v)){
            luvaesquerda->setSoco(true);
            delay.tiroA=10;
        }
    } else {
        delay.tiroA--;
        if (delay.tiroA<=6){
                luvaesquerda->setSoco(false);
        }
    }
	//Controle de Socos - Soco Direito
    if (delay.tiroB<=0){
        if((input->teclado->isKey(SDLK_b))){
            luvadireita->setSoco(true);
            delay.tiroB=10;
        }
    } else {
        delay.tiroB--;
        if (delay.tiroB<=6){
                luvadireita->setSoco(false);
        }
    }
}

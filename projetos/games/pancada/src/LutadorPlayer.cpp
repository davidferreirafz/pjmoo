
#include "LutadorPlayer.h"

LutadorPlayer::LutadorPlayer(){
	CabecaFactory cFactory;
	cabeca = cFactory.criar(FZ);
	olharCima();
}

LutadorPlayer::~LutadorPlayer(){

}

void LutadorPlayer::acao(InputSystem * input) 
{
	int passo=3;

	//Movimentação
	if ((input->teclado->isKey(SDLK_UP))||(input->joystick->isAxeUp())){
		posicao.y-=passo;
	} else if ((input->teclado->isKey(SDLK_DOWN))||(input->joystick->isAxeDown())){
		posicao.y+=passo;
	}
    if ((input->teclado->isKey(SDLK_LEFT))||(input->joystick->isAxeLeft())){
        posicao.x-=passo;
    } else if ((input->teclado->isKey(SDLK_RIGHT))||(input->joystick->isAxeRight())){
        posicao.x+=passo;
    }
	//Controle de Socos - Soco Esquerdo
    if (delay.tiroA<=0){
        if((input->teclado->isKey(SDLK_COMMA))||(input->joystick->isButtonA())){
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
        if((input->teclado->isKey(SDLK_PERIOD))||(input->joystick->isButtonB())){
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

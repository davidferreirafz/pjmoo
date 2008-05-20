
#include "LutadorPlayer.h"

LutadorPlayer::LutadorPlayer()
{
	CabecaFactory cFactory;
	cabeca = cFactory.criar(FZ);
	olharCima();
}
LutadorPlayer::~LutadorPlayer()
{

}
void LutadorPlayer::acao(GBF::Kernel::Input::InputSystem * input)
{
    //Movimentação
    if ((input->teclado->isKey(SDLK_UP))||(input->joystick->isAxeUp())){
        andarCima();
    } else if ((input->teclado->isKey(SDLK_DOWN))||(input->joystick->isAxeDown())){
        andarBaixo();
    }
    if ((input->teclado->isKey(SDLK_LEFT))||(input->joystick->isAxeLeft())){
        andarEsquerda();
    } else if ((input->teclado->isKey(SDLK_RIGHT))||(input->joystick->isAxeRight())){
        andarDireita();
    }

    //Controle de Socos - Soco Esquerdo
    socarEsquerda(((input->teclado->isKey(SDLK_COMMA))||(input->joystick->isButtonA())));
    //Controle de Socos - Soco Direito
    socarDireita(((input->teclado->isKey(SDLK_PERIOD))||(input->joystick->isButtonB())));
}

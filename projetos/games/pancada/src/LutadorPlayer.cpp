////    Pacanda - Based boxing game
////    Copyright (C) 2004-2006 David de Almeida Ferreira
////
////    This is free software; you can redistribute it and/or
////    modify it under the terms of the GNU General Public
////    License as published by the Free Software Foundation; either
////    version 2 of the License, or (at your option) any later version.
////
////    David de Almeida Ferreira (F-Z)
////        davidferreira@uol.com.br or davidferreira.fz@gmail.com
////        http://pjmoo.codigolivre.org.br
////////////////////////////////////////////////////////////////////////

#include "LutadorPlayer.h"

LutadorPlayer::LutadorPlayer() 
{
	CabecaFactory cFactory;
	cabeca = cFactory.criar(1);
	olharCima();
}
LutadorPlayer::~LutadorPlayer(){

}

void LutadorPlayer::acao(InputSystem * input) 
{
//	float passo=deslocar(100.0f);

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
//        tempo.tiroA-=deslocar(20);
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
//        tempo.tiroB-=deslocar(20);
        delay.tiroB--;
        if (delay.tiroB<=6){
                luvadireita->setSoco(false);
        }
    }
}

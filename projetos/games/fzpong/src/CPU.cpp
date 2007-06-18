/***************************************************************************
 *   FZPong <Game - Pong Clone>                                            *
 *   Copyright (C) 2007 by David Ferreira - FZ                             *
 *   davidferreira.fz@gmail.com - http://pjmoo.sourceforge.net             *
 ***************************************************************************
 *   Este programa é software livre; você pode redistribuí-lo e/ou         *
 *   modificá-lo sob os termos da Licença Pública Geral GNU, conforme      *
 *   publicada pela Free Software Foundation; tanto a versão 2 da          *
 *   Licença como (a seu critério) qualquer versão mais nova.              *
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "CPU.h"


CPU::CPU()
{
    GraphicSystemImageBufferManager *gsImageBufferManager=GraphicSystemImageBufferManager::getInstance();
    SpriteFactory *spriteFactory = new SpriteFactory(gsImageBufferManager->getImageBuffer("personagem"));
    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(15,21,14,80,1,1));
    delete(spriteFactory);
}

CPU::~CPU()
{
    //dtor
}
void CPU::iniciarVisao()
{
    raioVisao=380;
}
void CPU::aumentarVisao()
{
    raioVisao+=20;

    if (raioVisao>=getAreaTela().bottom){
        raioVisao=getAreaTela().bottom;
    }
}
void CPU::iniciar()
{
    setPosicao(0,(getAreaTela().bottom/2)-(getDimensao().h/2));
}

void CPU::acao(InputSystem * input)
{
	float qx, qy, qr; //para guardar o quadrado de x, y e raio

	Area visao;

	visao.left=posicao.x;
	visao.top=posicao.y;
	visao.right=getDimensao().w;
	visao.bottom=getDimensao().h;

    Area areaVisaoBola;
    Dimensao tavb = getVisaoBola().getDimensao();
    Ponto pavb    = getVisaoBola().getPosicao();

    areaVisaoBola.left   = pavb.x;
    areaVisaoBola.top    = pavb.y;
    areaVisaoBola.right  = tavb.w;
    areaVisaoBola.bottom = tavb.h;


	//quadrado da distância em x
	qx = std::pow(float((areaVisaoBola.left + areaVisaoBola.right/2) - (visao.left + visao.right/2)), 2);
	//quadrado da distância em y
	qy = std::pow(float((areaVisaoBola.top + areaVisaoBola.bottom/2) - (visao.top  + visao.bottom/2)), 2);
	//quadrado da soma dos raios
	qr = std::pow(float(raioVisao), 2);

	if (qx + qy <= qr){
        if (posicao.y+(getDimensao().h/4) <= getVisaoBola().getPosicao().y){
            descer();
        }
        if (posicao.y+getDimensao().h-(getDimensao().h/4) >= getVisaoBola().getPosicao().y){
            subir();
        }
	}
/*
//Apenas para facilitar os testes com a raquete do lado esquerdo
	if ((input->teclado->isKey(SDLK_UP))||(input->joystick->isAxeUp())){
        subir();
    } else if ((input->teclado->isKey(SDLK_DOWN))||(input->joystick->isAxeDown())){
        descer();
    }
*/
}

bool CPU::isColisao(PersonagemAbstract * personagem)
{
    if ((personagem->getPosicao().x <= posicao.x+getDimensao().w)&&
        (posicao.y + getDimensao().h >= personagem->getPosicao().y)&&
        (posicao.y <= personagem->getPosicao().y + personagem->getDimensao().h)){
            return true;
    } else {
        return false;
    }
}

Ponto CPU::saque()
{
    Ponto saque;

    saque.x=posicao.x+getDimensao().w;
    saque.y=posicao.y+rand()%(getDimensao().h-getVisaoBola().getDimensao().h);

    return saque;
}


/***************************************************************************
 *   FZPong <Game - Pong Clone>                                            *
 *   Copyright (C) 2007 by David Ferreira - FZ                             *
 *   davidferreira.fz@gmail.com - http://pjmoo.sourceforge.net             *
 ***************************************************************************
 *   Este programa � software livre; voc� pode redistribu�-lo e/ou         *
 *   modific�-lo sob os termos da Licen�a P�blica Geral GNU, conforme      *
 *   publicada pela Free Software Foundation; tanto a vers�o 2 da          *
 *   Licen�a como (a seu crit�rio) qualquer vers�o mais nova.              *
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
    adaptarVelocidade();
    setPosicao(0,(getAreaTela().bottom/2)-(getDimensao().h/2));
}

void CPU::acao(InputSystem * input)
{
    Area areaVisaoBola = IA::converter(getVisaoBola().getDimensao(),getVisaoBola().getPosicao());
	Area visao         = IA::converter(getDimensao(),getPosicao());

    Decisao decisao = IA::pensar(visao,areaVisaoBola,raioVisao,efeito);

    if (decisao==DECISAO_SUBIR){
        subir();
    } else if (decisao==DECISAO_DESCER){
        descer();
    }
}

bool CPU::isColisao(PersonagemAbstract * personagem)
{
    if ((personagem->getPosicao().x <= posicao.x+getDimensao().w)&&
        (posicao.y + getDimensao().h >= personagem->getPosicao().y)&&
        (posicao.y <= personagem->getPosicao().y + personagem->getDimensao().h)){
            efeito = Efeito(rand()%3);
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


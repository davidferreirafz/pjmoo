///***************************************************************************
// *   FZPong <Game - Pong Clone>                                            *
// *   Copyright (C) 2007 by David Ferreira - FZ                             *
// *   davidferreira.fz@gmail.com - http://pjmoo.sourceforge.net             *
// ***************************************************************************
// *   Este programa é software livre; você pode redistribuí-lo e/ou         *
// *   modificá-lo sob os termos da Licença Pública Geral GNU, conforme      *
// *   publicada pela Free Software Foundation; tanto a versão 2 da          *
// *   Licença como (a seu critério) qualquer versão mais nova.              *
// ***************************************************************************
// *   This program is free software; you can redistribute it and/or modify  *
// *   it under the terms of the GNU General Public License as published by  *
// *   the Free Software Foundation; either version 2 of the License, or     *
// *   (at your option) any later version.                                   *
// *                                                                         *
// *   You should have received a copy of the GNU General Public License     *
// *   along with this program; if not, write to the                         *
// *   Free Software Foundation, Inc.,                                       *
// *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
// ***************************************************************************/
#include "Jogador.h"

Jogador::Jogador(){

    GraphicSystemImageBufferManager *gsImageBufferManager=GraphicSystemImageBufferManager::getInstance();
    SpriteFactory *spriteFactory = new SpriteFactory(gsImageBufferManager->getImageBuffer("personagem"));
    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(0,21,14,80,1,1));
    delete(spriteFactory);
}

Jogador::~Jogador(){

    //dtor
}

void Jogador::iniciar() 
{
    adaptarVelocidade();
    setPosicao(getAreaTela().right-getDimensao().w,(getAreaTela().bottom/2)-(getDimensao().h/2));
}
void Jogador::acao(InputSystem * input) 
{
	/*if ((input->teclado->isKey(SDLK_UP))||(input->joystick->isAxeUp())){
        subir();
    } else if ((input->teclado->isKey(SDLK_DOWN))||(input->joystick->isAxeDown())){
        descer();
    }*/

    Area areaVisaoBola = IA::converter(getVisaoBola().getDimensao(),getVisaoBola().getPosicao());
	Area visao         = IA::converter(getDimensao(),getPosicao());

    Decisao decisao = IA::pensar(visao,areaVisaoBola,380,EFEITO_SEM);

    if (decisao==DECISAO_SUBIR){
        subir();
    } else if (decisao==DECISAO_DESCER){
        descer();
    }
}
bool Jogador::isColisao(PersonagemAbstract * personagem) 
{
    if ((personagem->getPosicao().x+personagem->getDimensao().w >= posicao.x)&&
        (posicao.y + getDimensao().h >= personagem->getPosicao().y)&&
        (posicao.y <= personagem->getPosicao().y + personagem->getDimensao().h)){
            return true;
    } else {
        return false;
    }
}
Ponto Jogador::saque() 
{
    Ponto saque;

    saque.x=posicao.x-getVisaoBola().getDimensao().w;
    saque.y=posicao.y+rand()%(getDimensao().h-getVisaoBola().getDimensao().h);

    return saque;
}

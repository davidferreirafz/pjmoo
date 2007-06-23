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
#include "Bola.h"


Bola::Bola()
{
    GraphicSystemImageBufferManager *gsImageBufferManager=GraphicSystemImageBufferManager::getInstance();
    SpriteFactory *spriteFactory = new SpriteFactory(gsImageBufferManager->getImageBuffer("personagem"));
    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(0,0,20,20,1,1));
    getSpritePrincipal()->setAutomatico(false);
    getSpritePrincipal()->setQtdDirecoes(2);
}

Bola::~Bola()
{
    //dtor
}

void Bola::acao(InputSystem * input)
{
    posicao.x+=int(velocidade.x);
    posicao.y+=int(velocidade.y);

    if (posicao.y+getDimensao().h>=getAreaTela().bottom){
        velocidade.y = - velocidade.y;
        posicao.y=getAreaTela().bottom-getDimensao().h;
        soundSystem->fxManager->playPanEffect("ping",posicao.x);
    } else if (posicao.y<=getAreaTela().top){
        velocidade.y = - velocidade.y;
        posicao.y=getAreaTela().top;
        soundSystem->fxManager->playPanEffect("ping",posicao.x);
    }

    if (posicao.x>=getAreaTela().right/2){
        getSpritePrincipal()->setDirecao(DR_DIREITA);
    } else {
        getSpritePrincipal()->setDirecao(DR_ESQUERDA);
    }
}
bool Bola::isColisao(PersonagemAbstract * personagem)
{
    bool colisao=personagem->isColisao(this);
    if (colisao){
        soundSystem->fxManager->playPanEffect("raquete",posicao.x);
        //bateu em baixo
        if (posicao.y>=personagem->getPosicao().y+personagem->getDimensao().h-getDimensao().h){

            if (posicao.x<=personagem->getPosicao().x){
                posicao.x=personagem->getPosicao().x-getDimensao().w-2;
            } else if (posicao.x>=personagem->getPosicao().x){
                posicao.x=personagem->getPosicao().x+getDimensao().w+2;
            }

            velocidade.x = - velocidade.x;
            //veio de baixo?
            if (velocidade.y<0){
                velocidade.y = - velocidade.y;
            }
        //bateu em cima
        } else if (posicao.y<=personagem->getPosicao().y+getDimensao().h){

            if (posicao.x<=personagem->getPosicao().x){
                posicao.x=personagem->getPosicao().x-getDimensao().w-2;
            } else if (posicao.x>=personagem->getPosicao().x){
                posicao.x=personagem->getPosicao().x+getDimensao().w+2;
            }

            velocidade.x = - velocidade.x;
            //veio de cima ?
            if (velocidade.y>0){
                velocidade.y = - velocidade.y;
            }
        //bateu no meio
        } else {

            if (posicao.x<=personagem->getPosicao().x){
                posicao.x=personagem->getPosicao().x-getDimensao().w-2;
            } else if (posicao.x>=personagem->getPosicao().x){
                posicao.x=personagem->getPosicao().x+getDimensao().w+2;
            }

            velocidade.x = - velocidade.x;
        }
    }

    return colisao;
}

void Bola::elevarGrauDificuldade()
{
    velocidadeGradativa.y+=0.20;
    velocidadeGradativa.x+=0.50;

    if (velocidadeGradativa.y>=getDimensao().w*0.8){
        velocidadeGradativa.y=int(getDimensao().w*0.8);
    }
    if (velocidadeGradativa.x>=getDimensao().w*0.9){
        velocidadeGradativa.x=int(getDimensao().w*0.9);
    }

    velocidade.y=velocidadeGradativa.y;
    velocidade.x=velocidadeGradativa.x;
}

void Bola::iniciar()
{
    velocidadeGradativa.x=8;
    velocidadeGradativa.y=4;
    continuar();
}

void Bola::continuar()
{
    elevarGrauDificuldade();

    if (rand()%10 % 2==0){
        velocidade.x = - velocidade.x;
    }

    if (rand()%10 % 2!=0){
        velocidade.y = - velocidade.y;
    }

    setPosicao((getAreaTela().right/2)-(getDimensao().w/2),getAreaTela().bottom/2-(getDimensao().h/2));
}

void Bola::iniciar(Ponto saque)
{
    elevarGrauDificuldade();
    setPosicao(saque.x,saque.y+getDimensao().h/2);
}






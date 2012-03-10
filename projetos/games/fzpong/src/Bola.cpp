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
#include "Bola.h"

Bola::Bola()
{
    GBF::Image::SpriteFactory *spriteFactory = new GBF::Image::SpriteFactory("personagem");

    addMainSprite(spriteFactory->createSpriteCharacter(0,0,20,20,1,1));
    getMainSprite()->animation.setAutomatic(false);
    getMainSprite()->setQtdDirecoes(2);
}
Bola::~Bola()
{

    //dtor
}
void Bola::iniciar()
{
    batidaParede=0;

    velocidadeGradativa.x=0;
    velocidadeGradativa.y=0;

    continuar();
}
void Bola::iniciar(GBF::Point saque)
{
    batidaParede=0;
    velocidadeGradativa.y=4+rand()%4;
    velocidadeGradativa.x=4+rand()%4;

    checkarVelocidade();

    setPoint(saque.x,saque.y+getDimension().h/2);
}
void Bola::continuar()
{
    batidaParede=0;

    velocidadeGradativa.y=4+rand()%4;
    velocidadeGradativa.x=6+rand()%4;

    checkarVelocidade();

    if (rand()%10 % 2==0){
        velocidade.x = - velocidade.x;
    }

    if (rand()%10 % 2!=0){
        velocidade.y = - velocidade.y;
    }

    setPoint((getAreaTela().right/2)-(getDimension().w/2),getAreaTela().bottom/2-(getDimension().h/2));
}
void Bola::update(GBF::Kernel::Input::InputSystem * input)
{
    point.x+=int(velocidade.x);
    point.y+=int(velocidade.y);

    if (point.y+getDimension().h>=getAreaTela().bottom){
        velocidade.y = - velocidade.y;
        point.y=getAreaTela().bottom-getDimension().h;
        soundSystem->fxManager->playPanEffect("ping",point.x);
        batidaParede++;
    } else if (point.y<=getAreaTela().top){
        velocidade.y = - velocidade.y;
        point.y=getAreaTela().top;
        soundSystem->fxManager->playPanEffect("ping",point.x);
        batidaParede++;
    }

    if (point.x>=getAreaTela().right/2){
        getMainSprite()->setDirection(GBF::Image::Sprite::DR_DIREITA);
    } else {
        getMainSprite()->setDirection(GBF::Image::Sprite::DR_ESQUERDA);
    }

    if (batidaParede>4){
        elevarGrauDificuldade();
        batidaParede=0;
    }
}
bool Bola::isCollision(Character * personagem)
{
    bool colisao=personagem->isCollision(this);
    if (colisao){
        soundSystem->fxManager->playPanEffect("raquete",point.x);


        int raquete   = personagem->getPoint().y;
        int areaBaixo = personagem->getDimension().h - 20;
        int areaCima  = 20;
        int bola      = point.y;

        //std::cout << "Bola" << bola << " Parede " << (raquete+areaBaixo) << std::endl;
        //bateu em baixo
        if (bola>=raquete+areaBaixo){
            //std::cout << "Baixo - v:" << velocidade.y << std::endl;
            corrigirEixoX(personagem);
            velocidade.y = velocidadeGradativa.y;
            //std::cout << "agora v:" << velocidade.y << std::endl;
        //bateu em cima
        } else if (bola<=raquete+areaCima){
            //std::cout << "Cima - v:" << velocidade.y << std::endl;
            corrigirEixoX(personagem);
            velocidade.y = - velocidadeGradativa.y;
            //std::cout << "agora v:" << velocidade.y << std::endl;
        //bateu no meio
        } else {
            corrigirEixoX(personagem);
            velocidade.y=0;
        }
        batidaParede++;
    }

    return colisao;
}
int Bola::getVelocidade()
{
    return int(velocidade.x);
}
//Corrigir a posição da bola após colidir com uma raquete, evitando que a bola seja desenha dentro/após a raquete
void Bola::corrigirEixoX(Character * personagem)
{
    //Colisão do lado direito da tela
    if (getMainSprite()->getDirection()==GBF::Image::Sprite::DR_DIREITA){
        if (point.x+getDimension().w>=personagem->getPoint().x){
            point.x=personagem->getPoint().x-getDimension().w;
            velocidade.x = - velocidade.x;
        }
    //Colisão do lado esquerdo da tela
    } else {
        if (point.x<=personagem->getPoint().x+personagem->getDimension().w){
            point.x=personagem->getPoint().x+personagem->getDimension().w;
            velocidade.x = - velocidade.x;
        }
    }
}
void Bola::elevarGrauDificuldade()
{
    velocidadeGradativa.y+=1+rand()%3;
    velocidadeGradativa.x+=1+rand()%2;

    checkarVelocidade();
}

void Bola::checkarVelocidade()
{
    int tLargura=int(getDimension().w*0.9);
    int tAltura=int(getDimension().h*0.9);

    if (velocidadeGradativa.y>=tAltura){
        velocidadeGradativa.y=tAltura;
    }
    if (velocidadeGradativa.x>=tLargura){
       velocidadeGradativa.x=tLargura;
    }

    if (velocidade.y>0){
        velocidade.y=velocidadeGradativa.y;
    } else if (velocidade.y<0){
        velocidade.y= - velocidadeGradativa.y;
    }

    if (velocidade.x>0){
        velocidade.x=velocidadeGradativa.x;
    } else {
        velocidade.x= - velocidadeGradativa.x;
    }
}


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
    GBF::Kernel::Graphic::GraphicSystem  *graphicSystem = GBF::Kernel::Graphic::GraphicSystem::getInstance();
    GBF::Grafico::SpriteFactory *spriteFactory = new GBF::Grafico::SpriteFactory(graphicSystem->imageBufferManager->getImageBuffer("personagem"));

    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(0,0,20,20,1,1));
    getSpritePrincipal()->animacao.setAutomatico(false);
    getSpritePrincipal()->setQtdDirecoes(2);
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
void Bola::iniciar(GBF::Ponto saque)
{
    batidaParede=0;
    velocidadeGradativa.y=4+rand()%4;
    velocidadeGradativa.x=4+rand()%4;

    checkarVelocidade();

    setPosicao(saque.x,saque.y+getDimensao().h/2);
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

    setPosicao((getAreaTela().right/2)-(getDimensao().w/2),getAreaTela().bottom/2-(getDimensao().h/2));
}
void Bola::acao(GBF::Kernel::Input::InputSystem * input)
{
    posicao.x+=int(velocidade.x);
    posicao.y+=int(velocidade.y);

    if (posicao.y+getDimensao().h>=getAreaTela().bottom){
        velocidade.y = - velocidade.y;
        posicao.y=getAreaTela().bottom-getDimensao().h;
        soundSystem->fxManager->playPanEffect("ping",posicao.x);
        batidaParede++;
    } else if (posicao.y<=getAreaTela().top){
        velocidade.y = - velocidade.y;
        posicao.y=getAreaTela().top;
        soundSystem->fxManager->playPanEffect("ping",posicao.x);
        batidaParede++;
    }

    if (posicao.x>=getAreaTela().right/2){
        getSpritePrincipal()->setDirecao(GBF::Grafico::Sprite::DR_DIREITA);
    } else {
        getSpritePrincipal()->setDirecao(GBF::Grafico::Sprite::DR_ESQUERDA);
    }

    if (batidaParede>4){
        elevarGrauDificuldade();
        batidaParede=0;
    }
}
bool Bola::isColisao(Personagem::Personagem * personagem)
{
    bool colisao=personagem->isColisao(this);
    if (colisao){
        soundSystem->fxManager->playPanEffect("raquete",posicao.x);


        int raquete   = personagem->getPosicao().y;
        int areaBaixo = personagem->getDimensao().h - 20;
        int areaCima  = 20;
        int bola      = posicao.y;

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
void Bola::corrigirEixoX(Personagem::Personagem * personagem)
{
    //Colisão do lado direito da tela
    if (getSpritePrincipal()->getDirecao()==GBF::Grafico::Sprite::DR_DIREITA){
        if (posicao.x+getDimensao().w>=personagem->getPosicao().x){
            posicao.x=personagem->getPosicao().x-getDimensao().w;
            velocidade.x = - velocidade.x;
        }
    //Colisão do lado esquerdo da tela
    } else {
        if (posicao.x<=personagem->getPosicao().x+personagem->getDimensao().w){
            posicao.x=personagem->getPosicao().x+personagem->getDimensao().w;
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
    int tLargura=int(getDimensao().w*0.9);
    int tAltura=int(getDimensao().h*0.9);

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


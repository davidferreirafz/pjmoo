/***************************************************************************
 *   Copyright (C) 2005-2006 by David Ferreira                             *
 *   davidferreira@uol.com.br - davidferreira.fz@gmail.com                 *
 *   http://pjmoo.codigolivre.org.br                                       *
 *       http://davidferreira.fz.googlepages.com                           *
 *                                                                         *
 *   Este programa é um software livre; você pode redistribui-lo e/ou      *
 *   modifica-lo dentro dos termos da Licença Pública Geral (GPL) GNU      *
 *   como publicada pela Fundação do Software Livre (FSF); na versão 2 da  *
 *   Licença.                                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include "NaveAliado.h"

ListTiroJogador* NaveAliado::listTiro=NULL;
void NaveAliado::setListTiro(ListTiroJogador* list)
{
    listTiro=list;
}
NaveAliado::NaveAliado()
{
    atingido=false;
    contagemChoque=0;
}
NaveAliado::~NaveAliado()
{
//	sprite=NULL;
//	sprite_atingido=NULL;
}
void NaveAliado::selecionarPosicao()
{
    Dimensao dimensao = getDimensao();
    setPosicao((area.right / 2)-(dimensao.w/2),(area.bottom) - dimensao.h); 
}
void NaveAliado::acao(InputSystem* INPUT)
{
	checarArma();

	if ((INPUT->teclado->isKey(SDLK_UP))||(INPUT->joystick->isAxeUp())){
		//sprite->setDirecao(DR_CIMA);
		getSpritePrincipal()->setDirecao(DR_CIMA);
        posicao.y-=getVelocidade();
    } else if ((INPUT->teclado->isKey(SDLK_DOWN))||(INPUT->joystick->isAxeDown())){
//        sprite->setDirecao(DR_CIMA);
        getSpritePrincipal()->setDirecao(DR_CIMA);
        posicao.y+=getVelocidade();
    } 
    if ((INPUT->teclado->isKey(SDLK_LEFT))||(INPUT->joystick->isAxeLeft())){
//        sprite->setDirecao(DR_ESQUERDA);
        getSpritePrincipal()->setDirecao(DR_ESQUERDA);
        posicao.x-=getVelocidade();
    } else if ((INPUT->teclado->isKey(SDLK_RIGHT))||(INPUT->joystick->isAxeRight())){
//        sprite->setDirecao(DR_DIREITA);
        getSpritePrincipal()->setDirecao(DR_DIREITA);
        posicao.x+=getVelocidade();
    }
     
    //Verifica Limites de Deslocamento da Nave    
    limite();
    
    //Prepara Arma Phaser
    if ((((INPUT->teclado->isKey(SDLK_LCTRL))||(INPUT->joystick->isButtonA()))&&(isAtivo()))){
        prepararPhaser();
    }
    //Prepara Arma Torpedo
    if ((((INPUT->teclado->isKey(SDLK_LALT))||(INPUT->joystick->isButtonB()))&&(isAtivo()))){
        prepararTorpedo();
    } else if ((INPUT->teclado->isKey(SDLK_a))||(INPUT->joystick->isButtonC())){
        aumentarVelocidadeDobra();
    } else if ((INPUT->teclado->isKey(SDLK_z))||(INPUT->joystick->isButtonD())){
        reduzirVelocidadeDobra();
    }
}
void NaveAliado::desenhar()
{
    if (isAtivo()){
        if (atingido){
//            sprite_atingido->desenhar(posicao.x,posicao.y);
            getSprite("explosao")->desenhar(posicao.x,posicao.y);
//            if (sprite_atingido->isAnimacaoFim()){
            if (getSprite("explosao")->isAnimacaoFim()){
                atingido=false;
                setVivo(true);
//                sprite_atingido->setAnimacaoInicio();
                getSprite("explosao")->setAnimacaoInicio();
            }
        } else {
           PersonagemAbstract::desenhar();
        }
    }
}
void NaveAliado::limite()
{  
    Dimensao dimensao = getDimensao();
    if (posicao.x<=area.left){
        posicao.x=area.left;
    } else if (posicao.x+dimensao.w>=area.right){
        posicao.x=area.right - dimensao.w;
    }
    if (posicao.y<=area.top){
        posicao.y=area.top;
    } else if (posicao.y+dimensao.h>=area.bottom){
        posicao.y=area.bottom - dimensao.h;
    }   
}
void NaveAliado::checarArma()
{
    delay.tiroA--;
    delay.tiroB--;    
}
void NaveAliado::setVivo(bool VALOR)
{
    if (VALOR==false){
        atingido=true;
        if (sistema.escudo.atual>0){
            VALOR=true;
            contagemChoque++;
            if (contagemChoque>50){
                contagemChoque=0;
                int velocidade = sistema.velocidade.eAtual;
                velocidade--;
                if (velocidade<VELOCIDADE_DOBRA_01){
                    velocidade=VELOCIDADE_DOBRA_01;
                }
                sistema.velocidade.eAtual      = (EnumVelocidadeDobra) velocidade;
//                sistema.velocidade.eDisponivel = (EnumVelocidadeDobra) velocidade;
            }
        }
    }  
    PersonagemAbstract::setVivo(VALOR);
}
void NaveAliado::choque(int forca)
{
    sistema.escudo.atual-=forca;
    
    if (sistema.escudo.atual<0){
        soundSystem->fxManager->playPanEffect("explosao",posicao.x);
        setVivo(false);        
    } else {
        atingido=true;
        contagemChoque++;
        if (contagemChoque>300){
            contagemChoque=0;
            int velocidade = sistema.velocidade.eAtual;
            velocidade--;
            if (velocidade<VELOCIDADE_DOBRA_01){
                velocidade=VELOCIDADE_DOBRA_01;
            }
            sistema.velocidade.eAtual      = (EnumVelocidadeDobra) velocidade;
            sistema.velocidade.eDisponivel = (EnumVelocidadeDobra) velocidade;
        }
    }    
}
void NaveAliado::prepararTorpedo()
{
    if (delay.tiroB<=0){
        dispararTorpedo();
        delay.tiroB=espera.tiroB;
    }
}
void NaveAliado::prepararPhaser()
{
    if (delay.tiroA<=0){
        dispararPhaser();
        delay.tiroA=espera.tiroA;
    }
}
void NaveAliado::colisao(ListItem* listItem)
{
	ItemAbstract *item = NULL;

    for (int iList=0; iList<listItem->size(); iList++){
        if (((item=listItem->getItem(iList))!=NULL)
            &&(item->isVivo())){
            if (isColisao(item)){
                item->setAtivo(false);
                switch(item->getTipo())
                {
                    case ITEM_ESCUDO:
                            sistema.escudo.atual += item->getBonus();
                        break;
                    case ITEM_ARMA:
                            sistema.arma.torpedo += item->getBonus();
                        break;
                    case ITEM_VELOCIDADE:
                            int velocidade = getVelocidade();
                            velocidade+=item->getBonus();
                            sistema.velocidade.eAtual =(EnumVelocidadeDobra)velocidade;
                            if (sistema.velocidade.eAtual>sistema.velocidade.eMaxima){
                                sistema.velocidade.eAtual=sistema.velocidade.eMaxima;
                            }
                            //Armazena nova velocidade diponivel, porem se ultrapassa
                            //a velocidade estabelecida deve ser invocada manualmente
                            sistema.velocidade.eDisponivel=(EnumVelocidadeDobra)velocidade;
                        break;
                }
                break;
            }
        }
    }
}
void NaveAliado::aumentarVelocidadeDobra()
{
    int velocidade = sistema.velocidade.eAtual;
    
    velocidade++;
    
    if (velocidade >= sistema.velocidade.eDisponivel){
        velocidade = sistema.velocidade.eDisponivel;
    }
    sistema.velocidade.eAtual = (EnumVelocidadeDobra) velocidade;
}
void NaveAliado::reduzirVelocidadeDobra()
{
    int velocidade = sistema.velocidade.eAtual;
    
    velocidade--;
    
    if (velocidade < VELOCIDADE_DOBRA_01){
        velocidade = VELOCIDADE_DOBRA_01;
    }
    sistema.velocidade.eAtual = (EnumVelocidadeDobra) velocidade;
}



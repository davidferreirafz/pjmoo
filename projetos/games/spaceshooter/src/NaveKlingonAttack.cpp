/***************************************************************************
 *   Copyright (C) 2005-2006 by David Ferreira                             *
 *   davidferreira@uol.com.br - davidferreira.fz@gmail.com                 *
 *   http://pjmoo.codigolivre.org.br                                       *
 *       http://davidferreira.fz.googlepages.com                           *
 *                                                                         *
 *   Este programa � um software livre; voc� pode redistribui-lo e/ou      *
 *   modifica-lo dentro dos termos da Licen�a P�blica Geral (GPL) GNU      *
 *   como publicada pela Funda��o do Software Livre (FSF); na vers�o 2 da  *
 *   Licen�a.                                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include "NaveKlingonAttack.h"

bool NaveKlingonAttack::cantando=false;
NaveKlingonAttack::NaveKlingonAttack()
{
    GraphicSystemImageBufferManager *gsImageBufferManager=GraphicSystemImageBufferManager::getInstance();

    SpriteFactory * spriteFactory   = new SpriteFactory(gsImageBufferManager->getImageBuffer("personagem"));
    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(0,199,55,55,1,2));
    delete (spriteFactory);

//    sprite->setQtdDirecoes(8);
    getSpritePrincipal()->setQtdDirecoes(8);
    selecionarPosicao();
//    caminho(sprite->getDirecao());
    caminho(getSpritePrincipal()->getDirecao());

    espera.tiroA=16;
    espera.tiroB=20;
    //usado para mudar ou nao direcao da nave
    delay.tiroD=espera.tiroD=4;

    sistema.arma.phaser   = 0;
    sistema.arma.plasma   = 0;
    sistema.arma.torpedo  = 30;
    sistema.escudo.atual  = 20;
    sistema.escudo.maximo = 20;
    sistema.velocidade.eMaxima = VELOCIDADE_DOBRA_05;
    sistema.velocidade.eAtual  = VELOCIDADE_DOBRA_03;

    if (!cantando){
    	soundSystem->fxManager->playPanEffect("klingonmsg",posicao.x);
    	cantando=true;
    }
}
NaveKlingonAttack::~NaveKlingonAttack()
{
    if (cantando){
        cantando=false;
    }
    //desaloca��o na classe base
    //UtilLog::getInstance()->status("[NaveKlingonBirdPrev]");
}
void NaveKlingonAttack::dispararPhaser()
{
    //Adiciona ao Pool
    listTiro->adicionar(new TiroPlasmaKlingon(posicao.x+27 ,posicao.y+27,TiroPlasmaKlingon::UP_RIGHT));
    listTiro->adicionar(new TiroPlasmaKlingon(posicao.x+27 ,posicao.y+27,TiroPlasmaKlingon::UP_LEFT));
    listTiro->adicionar(new TiroPlasmaKlingon(posicao.x+27 ,posicao.y+27,TiroPlasmaKlingon::DOWN_RIGHT));
    listTiro->adicionar(new TiroPlasmaKlingon(posicao.x+27 ,posicao.y+27,TiroPlasmaKlingon::DOWN_LEFT));
    //Efeito Sonoro
	soundSystem->fxManager->playPanEffect("tiro",posicao.x);
    //Mudando direcao da Nave
	delay.tiroD--;
	if (delay.tiroD<=0){
        delay.tiroD=espera.tiroD;
        caminho();
    }
}
void NaveKlingonAttack::dispararTorpedo()
{
//nave sem torpedo
}


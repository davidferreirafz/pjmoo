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
#include "NaveKlingonBirdPrev.h"

NaveKlingonBirdPrev::NaveKlingonBirdPrev()
{
    GraphicSystemImageBufferManager *gsImageBufferManager=GraphicSystemImageBufferManager::getInstance();

    SpriteFactory * spriteFactory   = new SpriteFactory(gsImageBufferManager->getImageBuffer("personagem"));
    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(221,255,55,55,1,2));
    delete (spriteFactory);

//    sprite->setQtdDirecoes(4);
    getSpritePrincipal()->setQtdDirecoes(4);
    selecionarPosicao();
//    caminho(sprite->getDirecao());
    caminho(getSpritePrincipal()->getDirecao());

    espera.tiroA=8;
    espera.tiroB=20;
    //usado para mudar ou nao direcao da nave
    delay.tiroD=espera.tiroD=6;

    sistema.arma.phaser   = 0;
    sistema.arma.plasma   = 0;
    sistema.arma.torpedo  = 0;
    sistema.escudo.atual  = 10;
    sistema.escudo.maximo = 10;
    sistema.velocidade.eMaxima = VELOCIDADE_DOBRA_04;
    sistema.velocidade.eAtual  = VELOCIDADE_DOBRA_03;

}
NaveKlingonBirdPrev::~NaveKlingonBirdPrev()
{
    //desaloca��o na classe base
    //UtilLog::getInstance()->status("[NaveKlingonAttack]");
}
void NaveKlingonBirdPrev::dispararPhaser()
{
    //Adiciona ao Pool
//    switch(sprite->getDirecao()){
    switch(getSpritePrincipal()->getDirecao()){
        case DR_CIMA:
                listTiro->adicionar(new TiroPlasmaKlingon(posicao.x+26,posicao.y+2,TiroPlasmaKlingon::UP));
            break;
        case DR_DIREITA:
                listTiro->adicionar(new TiroPlasmaKlingon(posicao.x+50,posicao.y+26,TiroPlasmaKlingon::RIGHT));
            break;
        case DR_BAIXO:
                listTiro->adicionar(new TiroPlasmaKlingon(posicao.x+26,posicao.y+50,TiroPlasmaKlingon::DOWN));
            break;
        case DR_ESQUERDA:
                listTiro->adicionar(new TiroPlasmaKlingon(posicao.x+2,posicao.y+26,TiroPlasmaKlingon::LEFT));
            break;
        default:
                //Op��o default apenas para satisfa��o do compilador
                //Este metodo trata realmente apenas as condi��es acima
                //qualquer outra op��o n�o causa efeito
            break;
    }
    //Efeito Sonoro
	soundSystem->fxManager->playPanEffect("tiro",posicao.x);
    //Mudando direcao da Nave
	delay.tiroD--;
	if (delay.tiroD<=0){
        delay.tiroD=espera.tiroD;
        caminho();
    }
}
void NaveKlingonBirdPrev::dispararTorpedo()
{
//nave sem torpedo
}


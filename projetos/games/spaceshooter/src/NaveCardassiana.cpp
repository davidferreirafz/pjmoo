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
#include "NaveCardassiana.h"

NaveCardassiana::NaveCardassiana()
{
    GraphicSystemImageBufferManager *gsImageBufferManager=GraphicSystemImageBufferManager::getInstance();

    SpriteFactory * spriteFactory   = new SpriteFactory(gsImageBufferManager->getImageBuffer("personagem"));
    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(137,481,40,40,1,2));
    delete (spriteFactory);

//    sprite->setQtdDirecoes(4);
    getSpritePrincipal()->setQtdDirecoes(4);

    selecionarPosicao();
//    caminho(sprite->getDirecao());
    caminho(getSpritePrincipal()->getDirecao());

    //usado para mudar ou nao direcao da nave
    delay.tiroD=espera.tiroD=3;
    espera.tiroA=8;
    espera.tiroB=8;

    sistema.arma.phaser   = 0;
    sistema.arma.plasma   = 4;
    sistema.arma.torpedo  = 10;
    sistema.escudo.atual  = 16;
    sistema.escudo.maximo = 20;
    sistema.velocidade.eMaxima = VELOCIDADE_DOBRA_05;
    sistema.velocidade.eAtual  = VELOCIDADE_DOBRA_04;
}
NaveCardassiana::~NaveCardassiana()
{
    //desaloca��o na classe base
    //UtilLog::getInstance()->status("[NaveRomulana]");
}
void NaveCardassiana::dispararPhaser()
{
}
void NaveCardassiana::dispararTorpedo()
{
    //Adiciona ao Pool
//    switch(sprite->getDirecao()){
    switch(getSpritePrincipal()->getDirecao()){
        case DR_CIMA:
                listTiro->adicionar(new TiroTorpedoCardassiano(posicao.x+13,posicao.y,TiroTorpedoCardassiano::UP));
            break;
        case DR_DIREITA:
                listTiro->adicionar(new TiroTorpedoCardassiano(posicao.x+36,posicao.y+12,TiroTorpedoCardassiano::RIGHT));
            break;
        case DR_BAIXO:
                listTiro->adicionar(new TiroTorpedoCardassiano(posicao.x+13,posicao.y+39,TiroTorpedoCardassiano::DOWN));
            break;
        case DR_ESQUERDA:
                listTiro->adicionar(new TiroTorpedoCardassiano(posicao.x,posicao.y+12,TiroTorpedoCardassiano::LEFT));
            break;
        default:
                //Op��o default apenas para satisfa��o do compilador
                //Este metodo trata realmente apenas as condi��es acima
                //qualquer outra op��o n�o causa efeito
            break;
    }
	//Efeito Sonoro
	soundSystem->fxManager->playPanEffect("tiro",posicao.x);
	delay.tiroD--;
	if (delay.tiroD<=0){
        delay.tiroD=espera.tiroD;
        caminho();
    }
}



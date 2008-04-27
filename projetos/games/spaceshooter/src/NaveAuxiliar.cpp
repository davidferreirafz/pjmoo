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
#include "NaveAuxiliar.h"

NaveAuxiliar::NaveAuxiliar()
{
    GraphicSystemImageBufferManager *gsImageBufferManager=GraphicSystemImageBufferManager::getInstance();

    SpriteFactory * spriteFactory   = new SpriteFactory(gsImageBufferManager->getImageBuffer("personagem"));
    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(298,171,20,27,3,6));
//    sprite_atingido=spriteFactory->criarSpritePersonagem(359,171,20,27,3,6);
    adicionarSprite(spriteFactory->criarSpritePersonagem(359,171,20,27,3,6),"explosao");

    delete (spriteFactory);

    //sprite->setQtdDirecoes(1);
    getSpritePrincipal()->setQtdDirecoes(1);
//    sprite_atingido->setAutomatico(true);

    espera.tiroA = 4;
    espera.tiroB = 10;

    sistema.arma.phaser   = 0;
    sistema.arma.plasma   = 0;
    sistema.arma.torpedo  = 4;
    sistema.escudo.atual  = 15;
    sistema.escudo.maximo = 30;
    sistema.velocidade.eMaxima = VELOCIDADE_DOBRA_04;
    sistema.velocidade.eAtual  = VELOCIDADE_DOBRA_03;
    sistema.velocidade.eDisponivel = sistema.velocidade.eAtual;
    selecionarPosicao();
}
NaveAuxiliar::~NaveAuxiliar()
{
//desalocação na classe base
}
void NaveAuxiliar::dispararPhaser()
{
	//Adiciona ao Pool
	listTiro->adicionar(new TiroPhaserFE(posicao.x+9,posicao.y-4,TiroPhaserFE::UP));
	//Efeito Sonoro
	soundSystem->fxManager->playPanEffect("tiro",posicao.x);
}
void NaveAuxiliar::dispararTorpedo()
{
    if (sistema.arma.torpedo>0){
        sistema.arma.torpedo--;
        //Adicionar ao Pool
        listTiro->adicionar(new TiroTorpedoFE(posicao.x-5 ,posicao.y+5 ,TiroTorpedoFE::UP));
        listTiro->adicionar(new TiroTorpedoFE(posicao.x+11,posicao.y+5 ,TiroTorpedoFE::UP));
        //Efeito Sonoro
		soundSystem->fxManager->playPanEffect("tiro",posicao.x);
    }
}



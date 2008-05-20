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
#include "NaveVoyager.h"

NaveVoyager::NaveVoyager()
{
    GBF::Imagem::SpriteFactory  *spriteFactory = new GBF::Imagem::SpriteFactory("personagem");
    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(289,0,24,60,3,6));
//    sprite_atingido=spriteFactory->criarSpritePersonagem(362,0,24,60,3,6);
    adicionarSprite(spriteFactory->criarSpritePersonagem(362,0,24,60,3,6),"explosao");

    delete (spriteFactory);

//    sprite->setQtdDirecoes(1);
    getSpritePrincipal()->setQtdDirecoes(1);
//    sprite_atingido->setAutomatico(true);

    espera.tiroA = 4;
    espera.tiroB = 10;

    sistema.arma.phaser   = 0;
    sistema.arma.plasma   = 0;
    sistema.arma.torpedo  = 150;
    sistema.escudo.atual  = 80;
    sistema.escudo.maximo = 100;
    sistema.velocidade.eMaxima = VELOCIDADE_DOBRA_08;
    sistema.velocidade.eAtual  = VELOCIDADE_DOBRA_03;
    sistema.velocidade.eDisponivel = sistema.velocidade.eAtual;
    selecionarPosicao();
}
NaveVoyager::~NaveVoyager()
{
//desalocação na classe base
}
void NaveVoyager::dispararPhaser()
{
    listTiro->adicionar(new TiroPhaserFE(posicao.x   ,posicao.y+10,TiroPhaserFE::DOWN_LEFT));
    listTiro->adicionar(new TiroPhaserFE(posicao.x+22,posicao.y+10,TiroPhaserFE::DOWN_RIGHT));
    listTiro->adicionar(new TiroPhaserFE(posicao.x   ,posicao.y+41,TiroPhaserFE::UP));
    listTiro->adicionar(new TiroPhaserFE(posicao.x+22,posicao.y+41,TiroPhaserFE::UP));
    listTiro->adicionar(new TiroPhaserFE(posicao.x+1 ,posicao.y+55,TiroPhaserFE::DOWN));
    listTiro->adicionar(new TiroPhaserFE(posicao.x+22,posicao.y+55,TiroPhaserFE::DOWN));
	//Efeito Sonoro
    soundSystem->fxManager->playPanEffect("tiro",posicao.x);
}
void NaveVoyager::dispararTorpedo()
{
    if (sistema.arma.torpedo>0){
        sistema.arma.torpedo--;
        listTiro->adicionar(new TiroTorpedoFE(posicao.x-4 ,posicao.y+10,TiroTorpedoFE::UP_LEFT));
        listTiro->adicionar(new TiroTorpedoFE(posicao.x   ,posicao.y   ,TiroTorpedoFE::UP));
        listTiro->adicionar(new TiroTorpedoFE(posicao.x+9 ,posicao.y   ,TiroTorpedoFE::UP));
        listTiro->adicionar(new TiroTorpedoFE(posicao.x+15,posicao.y+10,TiroTorpedoFE::UP_RIGHT));
        //Efeito Sonoro
        soundSystem->fxManager->playPanEffect("tiro",posicao.x);
    }
}

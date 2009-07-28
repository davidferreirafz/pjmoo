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
#include "NaveEnterprise.h"

NaveEnterprise::NaveEnterprise()
{
    GBF::Imagem::SpriteFactory  *spriteFactory = new GBF::Imagem::SpriteFactory("personagem");
    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(0,150,37,48,2,2));
    adicionarSprite(spriteFactory->criarSpritePersonagem(75,150,37,48,6,2),"explosao");

    delete (spriteFactory);

    getSpritePrincipal()->setQtdDirecoes(1);

    espera.tiroA =  6;
    espera.tiroB = 15;

    sistema.arma.phaser   = 0;
    sistema.arma.plasma   = 0;
    sistema.arma.torpedo  = 50;
    sistema.escudo.atual  = 60;
    sistema.escudo.maximo = 80;
    sistema.velocidade.eMaxima = VELOCIDADE_DOBRA_05;
    sistema.velocidade.eAtual  = VELOCIDADE_DOBRA_03;
    sistema.velocidade.eDisponivel = sistema.velocidade.eAtual;
    selecionarPosicao();

    setRecarregarPhaser(10);
    setRecarregarTorpedo(10);
}
NaveEnterprise::~NaveEnterprise()
{
//desalocação na classe base
}
void NaveEnterprise::dispararPhaser()
{
    listTiro->adicionar(new TiroPhaserFE(posicao.x+6 ,posicao.y   ,TiroPhaserFE::UP));
    listTiro->adicionar(new TiroPhaserFE(posicao.x+29,posicao.y   ,TiroPhaserFE::UP));
    listTiro->adicionar(new TiroPhaserFE(posicao.x+11,posicao.y   ,TiroPhaserFE::UP));
    listTiro->adicionar(new TiroPhaserFE(posicao.x+24,posicao.y   ,TiroPhaserFE::UP));
    listTiro->adicionar(new TiroPhaserFE(posicao.x+8 ,posicao.y+48,TiroPhaserFE::DOWN));
    listTiro->adicionar(new TiroPhaserFE(posicao.x+29,posicao.y+48,TiroPhaserFE::DOWN));
    listTiro->adicionar(new TiroPhaserFE(posicao.x+16,posicao.y+48,TiroPhaserFE::DOWN));
    listTiro->adicionar(new TiroPhaserFE(posicao.x+21,posicao.y+48,TiroPhaserFE::DOWN));
    //Efeito Sonoro
    soundSystem->fxManager->playPanEffect("tiro",posicao.x);
}
void NaveEnterprise::dispararTorpedo()
{
    if (sistema.arma.torpedo>0){
        sistema.arma.torpedo--;
        //Adicionar ao Pool
        listTiro->adicionar(new TiroTorpedoFE(posicao.x   ,posicao.y+5,TiroTorpedoFE::UP_LEFT));
        listTiro->adicionar(new TiroTorpedoFE(posicao.x+12,posicao.y  ,TiroTorpedoFE::UP_LEFT));
        listTiro->adicionar(new TiroTorpedoFE(posicao.x+12,posicao.y  ,TiroTorpedoFE::UP));
        listTiro->adicionar(new TiroTorpedoFE(posicao.x+12,posicao.y  ,TiroTorpedoFE::UP_RIGHT));
        listTiro->adicionar(new TiroTorpedoFE(posicao.x+23,posicao.y+5,TiroTorpedoFE::UP_RIGHT));
	     //Efeito Sonoro
		soundSystem->fxManager->playPanEffect("tiro",posicao.x);
    }
}

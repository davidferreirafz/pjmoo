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
#include "NaveEnterpriseE.h"

NaveEnterpriseE::NaveEnterpriseE()
{
    GBF::Imagem::SpriteFactory  *spriteFactory = new GBF::Imagem::SpriteFactory("personagem");
    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(129,82,20,56,3,3));
    adicionarSprite(spriteFactory->criarSpritePersonagem(190,82,20,56,6,3),"explosao");

    delete (spriteFactory);

    getSpritePrincipal()->setQtdDirecoes(1);

    espera.tiroA = 5;
    espera.tiroB = 8;

    sistema.arma.phaser   = 0;
    sistema.arma.plasma   = 0;
    sistema.arma.torpedo  = 100;
    sistema.escudo.atual  = 80;
    sistema.escudo.maximo = 150;
    sistema.velocidade.eMaxima = VELOCIDADE_DOBRA_09;
    sistema.velocidade.eAtual  = VELOCIDADE_DOBRA_03;
    sistema.velocidade.eDisponivel = sistema.velocidade.eAtual;
    selecionarPosicao();

    setRecarregarPhaser(6);
    setRecarregarTorpedo(5);
}
NaveEnterpriseE::~NaveEnterpriseE()
{
//desalocação no destrutor base
}
void NaveEnterpriseE::dispararPhaser()
{
    listTiro->adicionar(new TiroPlasmaFE(posicao.x+8 ,posicao.y,TiroPlasmaFE::UP));
    listTiro->adicionar(new TiroPlasmaFE(posicao.x+1 ,posicao.y+20,TiroPlasmaFE::UP_RIGHT));
    listTiro->adicionar(new TiroPlasmaFE(posicao.x+1 ,posicao.y+43,TiroPlasmaFE::UP_LEFT));
    listTiro->adicionar(new TiroPlasmaFE(posicao.x+14,posicao.y+20,TiroPlasmaFE::UP_LEFT));
    listTiro->adicionar(new TiroPlasmaFE(posicao.x+14,posicao.y+43,TiroPlasmaFE::UP_RIGHT));
    listTiro->adicionar(new TiroPlasmaFE(posicao.x+1 ,posicao.y+20,TiroPlasmaFE::DOWN_RIGHT));
    listTiro->adicionar(new TiroPlasmaFE(posicao.x+14,posicao.y+20,TiroPlasmaFE::DOWN_LEFT));
    listTiro->adicionar(new TiroPlasmaFE(posicao.x+1 ,posicao.y+53,TiroPlasmaFE::DOWN_RIGHT));
    listTiro->adicionar(new TiroPlasmaFE(posicao.x+14,posicao.y+53,TiroPlasmaFE::DOWN_LEFT));
    listTiro->adicionar(new TiroPlasmaFE(posicao.x+8 ,posicao.y+53,TiroPlasmaFE::DOWN));
    //Efeito Sonoro
	soundSystem->fxManager->playPanEffect("tiro",posicao.x);
}
void NaveEnterpriseE::dispararTorpedo()
{
    if (sistema.arma.torpedo>0){
        sistema.arma.torpedo--;
        //Adicionar ao Pool
        listTiro->adicionar(new TiroTorpedoFE(posicao.x+11,posicao.y+50,TiroTorpedoFE::UP_LEFT));
        listTiro->adicionar(new TiroTorpedoFE(posicao.x+4 ,posicao.y+24,TiroTorpedoFE::UP_LEFT));
        listTiro->adicionar(new TiroTorpedoFE(posicao.x-5 ,posicao.y+5 ,TiroTorpedoFE::UP));
        listTiro->adicionar(new TiroTorpedoFE(posicao.x+11,posicao.y+5 ,TiroTorpedoFE::UP));
        listTiro->adicionar(new TiroTorpedoFE(posicao.x+5 ,posicao.y+24,TiroTorpedoFE::UP_RIGHT));
        listTiro->adicionar(new TiroTorpedoFE(posicao.x-5 ,posicao.y+50,TiroTorpedoFE::UP_RIGHT));
        listTiro->adicionar(new TiroTorpedoFE(posicao.x+2 ,posicao.y+50,TiroTorpedoFE::DOWN));
        //Efeito Sonoro
		soundSystem->fxManager->playPanEffect("tiro",posicao.x);
    }
}

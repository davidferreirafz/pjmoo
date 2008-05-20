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
#include "NaveRomulana.h"

NaveRomulana::NaveRomulana()
{
    GBF::Imagem::SpriteFactory  *spriteFactory = new GBF::Imagem::SpriteFactory("personagem");
    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(0,367,39,39,2,50));
    delete (spriteFactory);

//    sprite->setQtdDirecoes(4);
    getSpritePrincipal()->setQtdDirecoes(4);

    selecionarPosicao();
//    caminho(sprite->getDirecao());
    caminho(getSpritePrincipal()->getDirecao());

    //usado para mudar ou nao direcao da nave
    delay.tiroD=espera.tiroD=3;
    espera.tiroA=30;
    espera.tiroB=20;

    sistema.arma.phaser   = 0;
    sistema.arma.plasma   = 0;
    sistema.arma.torpedo  = 30;
    sistema.escudo.atual  = 30;
    sistema.escudo.maximo = 30;
    sistema.velocidade.eMaxima = VELOCIDADE_DOBRA_04;
    sistema.velocidade.eAtual  = VELOCIDADE_DOBRA_03;
}
NaveRomulana::~NaveRomulana()
{
    //desalocação na classe base
    //UtilLog::getInstance()->status("[NaveRomulana]");
}
void NaveRomulana::dispararPhaser()
{
    //Adiciona ao Pool
//    switch(sprite->getDirecao()){
    switch(getSpritePrincipal()->getDirecao()){
        case GBF::Imagem::Sprite::DR_CIMA:
                listTiro->adicionar(new TiroTorpedoRomulano(posicao.x+13,posicao.y,TiroTorpedoRomulano::UP));
            break;
        case GBF::Imagem::Sprite::DR_DIREITA:
                listTiro->adicionar(new TiroTorpedoRomulano(posicao.x+36,posicao.y+12,TiroTorpedoRomulano::RIGHT));
            break;
        case GBF::Imagem::Sprite::DR_BAIXO:
                listTiro->adicionar(new TiroTorpedoRomulano(posicao.x+13,posicao.y+39,TiroTorpedoRomulano::DOWN));
            break;
        case GBF::Imagem::Sprite::DR_ESQUERDA:
                listTiro->adicionar(new TiroTorpedoRomulano(posicao.x,posicao.y+12,TiroTorpedoRomulano::LEFT));
            break;
        default:
                //Opção default apenas para satisfação do compilador
                //Este metodo trata realmente apenas as condições acima
                //qualquer outra opção não causa efeito
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
void NaveRomulana::dispararTorpedo()
{
//Nave sem Torpedos
}



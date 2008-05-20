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
#include "NaveMiniBorg.h"

NaveMiniBorg::NaveMiniBorg()
{
    GBF::Imagem::SpriteFactory  *spriteFactory = new GBF::Imagem::SpriteFactory("personagem");
    adicionarSpritePrincipal(spriteFactory->criarSpritePersonagem(0,438,42,42,8,2));
    delete (spriteFactory);

//    sprite->setQtdDirecoes(1);
    getSpritePrincipal()->setQtdDirecoes(1);

    espera.tiroA=5;
    espera.tiroB=0;

    sistema.arma.phaser   = 10;
    sistema.arma.plasma   = 10;
    sistema.arma.torpedo  = 0;
    sistema.escudo.atual  = 10;
    sistema.escudo.maximo = 10;
    sistema.velocidade.eMaxima = VELOCIDADE_DOBRA_04;
    sistema.velocidade.eAtual  = VELOCIDADE_DOBRA_03;


    posicionar(rand()%(area.right-area.left-42),0,GBF::Imagem::Sprite::DR_BAIXO);
}
NaveMiniBorg::~NaveMiniBorg()
{
    //desalocação na classe base
    //UtilLog::getInstance()->status("[NaveMiniBorg]");
}
void NaveMiniBorg::posicionar(int x, int y, GBF::Imagem::Sprite::Direcao direcaoOriginal)
{
    setPosicao(x,y);
    caminho(direcaoOriginal);
    soundSystem->fxManager->play("borgmsg");
}
void NaveMiniBorg::dispararPhaser()
{
    listTiro->adicionar(new TiroPhaserBorg(posicao.x+14,posicao.y+14,TiroPhaserBorg::DOWN));
    listTiro->adicionar(new TiroPhaserBorg(posicao.x+14,posicao.y+14,TiroPhaserBorg::LEFT));
    listTiro->adicionar(new TiroPhaserBorg(posicao.x+14,posicao.y+14,TiroPhaserBorg::RIGHT));
    listTiro->adicionar(new TiroPhaserBorg(posicao.x+14,posicao.y,TiroPhaserBorg::UP));

    //Efeito Sonoro
	soundSystem->fxManager->playPanEffect("tiro",posicao.x);
}
void NaveMiniBorg::dispararTorpedo()
{
//Nave sem torpedo
}



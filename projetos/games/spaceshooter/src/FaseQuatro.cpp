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
#include "FaseQuatro.h"


FaseQuatro::FaseQuatro()
{
	delay.acao  = 10;
	delay.tiroA = 10;

    zona    = "fase_4_zona";
    missao  = "fase_4_missao";
    inimigo = "fase_4_inimigo";

    areaZona.left   =  59;
    areaZona.top    = 159;
    areaZona.bottom =  50;
    areaZona.right  = 518;
}
FaseQuatro::~FaseQuatro()
{
//Classe FaseAbstract remove o som da 'fase'
    soundSystem->fxManager->apagar("klingonmsg");
}
void FaseQuatro::configurar()
{
    tiles->setFrame(0,0,480,480);
    tiles->setTiles(15,400);
    tiles->setPixelTile(32,32);
    tiles->iniciarRandomico(6);

    soundSystem->musicManager->carregar("fase","data//som//004.ogg");
    soundSystem->fxManager->carregar("klingonmsg","data//som//klingonmsg.ogg");
    soundSystem->fxManager->setVolume("klingonmsg",60);
}
void FaseQuatro::iniciar()
{
    tiles->camera.setBottom();
    ListSpaceObstaculo::getInstance()->setLimite(10);

    ListSpaceObstaculo::OBSTACULO_ESFERA   = false;
    ListSpaceObstaculo::OBSTACULO_ASTEROID = false;
    ListSpaceObstaculo::OBSTACULO_MINA     = true;
    ListSpaceObstaculo::OBSTACULO_FURACAO  = false;

    soundSystem->musicManager->playInfinity("fase");

    nave = NaveFactory::criarNaveAliada(NaveFactory::VOYAGER);
}
void FaseQuatro::condicaoNavegandoFase()
{
    delay.acao--;

    if (delay.acao<=0){
        delay.acao=200;

        int selecao=rand()%4;

        switch(selecao){
            case 0:
                ListSpaceInimigo::getInstance()->adicionar(new NaveRomulana());
                ListSpaceInimigo::getInstance()->adicionar(new NaveRomulana());
                ListSpaceInimigo::getInstance()->adicionar(new NaveRomulana());
                break;
            case 1:
                ListSpaceInimigo::getInstance()->adicionar(new NaveKlingonBirdPrev());
                ListSpaceInimigo::getInstance()->adicionar(new NaveKlingonBirdPrev());
                ListSpaceInimigo::getInstance()->adicionar(new NaveKlingonBirdPrev());
                break;
            case 2:
                ListSpaceInimigo::getInstance()->adicionar(new NaveKlingonAttack());
                ListSpaceInimigo::getInstance()->adicionar(new NaveKlingonAttack());
                break;
            case 3:
                ListSpaceInimigo::getInstance()->adicionar(new NaveKlingonBirdPrev());
                ListSpaceInimigo::getInstance()->adicionar(new NaveKlingonAttack());
                ListSpaceInimigo::getInstance()->adicionar(new NaveKlingonBirdPrev());
                break;
        }
    }
}
void FaseQuatro::condicaoUnicaUltimoQuadro()
{
//Condição realizada apenas 1 vez, logo ao se chegar no ultimo quadro
//Ideal para gatilhos/triggers
    ListSpaceObstaculo::OBSTACULO_ESFERA   = false;
    ListSpaceObstaculo::OBSTACULO_ASTEROID = false;
    ListSpaceObstaculo::OBSTACULO_MINA     = false;
    ListSpaceObstaculo::OBSTACULO_FURACAO  = false;
}
bool FaseQuatro::isTerminou()
{
    if ((tiles->camera.isTop())&&(nave->getPosicao().y==0)){
        return true;
    } else {
        return false;
    }
}
std::string FaseQuatro::getMissaoCompleta()
{
	return "Fase 4";
}


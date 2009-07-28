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
#include "FaseCinco.h"


FaseCinco::FaseCinco()
{
	delay.acao  = 300;
	delay.tiroA = 10;

    zona    = "fase_5_zona";
    missao  = "fase_5_missao";
    inimigo = "fase_5_inimigo";

    areaZona.left   =  59;
    areaZona.top    = 118;
    areaZona.bottom =  41;
    areaZona.right  = 518;
}
FaseCinco::~FaseCinco()
{
//Classe FaseAbstract remove o som da 'fase'
}
void FaseCinco::configurar()
{
    tileSpace->setFrame(0,0,480,448);
    tileSpace->setTiles(15,142);
    tileSpace->setPixelTile(32,32);
    tileSpace->iniciarRandomico(6);

    soundSystem->musicManager->carregar("fase","data//som//005.ogg");
}
void FaseCinco::iniciar()
{
    tileSpace->camera.setBottom();
    ListSpaceObstaculo::getInstance()->setLimite(10);

    ListSpaceObstaculo::OBSTACULO_ESFERA   = true;
    ListSpaceObstaculo::OBSTACULO_ASTEROID = true;
    ListSpaceObstaculo::OBSTACULO_MINA     = true;
    ListSpaceObstaculo::OBSTACULO_FURACAO  = true;

    soundSystem->musicManager->playInfinity("fase");

    nave = NaveFactory::criarNaveAliada(NaveFactory::VOYAGER);
}
void FaseCinco::condicaoNavegandoFase()
{
    delay.acao--;

    if (delay.acao<=0){
        delay.acao=400;

        int selecao=rand()%2;

        switch(selecao){
            case 0:
                ListSpaceInimigo::getInstance()->adicionar(new NaveRomulana());
                ListSpaceInimigo::getInstance()->adicionar(new NaveRomulana());
                break;
            case 1:
                ListSpaceInimigo::getInstance()->adicionar(new NaveKlingonBirdPrev());
                ListSpaceInimigo::getInstance()->adicionar(new NaveKlingonAttack());
                break;
        }
    }
}
void FaseCinco::condicaoUnicaUltimoQuadro()
{
//Condição realizada apenas 1 vez, logo ao se chegar no ultimo quadro
//Ideal para gatilhos/triggers
    ListSpaceObstaculo::OBSTACULO_ESFERA   = false;
    ListSpaceObstaculo::OBSTACULO_ASTEROID = false;
    ListSpaceObstaculo::OBSTACULO_MINA     = false;
    ListSpaceObstaculo::OBSTACULO_FURACAO  = false;
}

std::string FaseCinco::getMissaoCompleta()
{
	return "Fase 5";
}

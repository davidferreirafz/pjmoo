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

#include "FaseTres.h"

FaseTres::FaseTres()
{
    delay.acao  = 10;
    delay.tiroA = 10;

    zona    = "fase_3_zona";
    missao  = "fase_3_missao";
    inimigo = "fase_3_inimigo";

    areaZona.left   =  59;
    areaZona.top    = 209;
    areaZona.bottom =  65;
    areaZona.right  = 518;
}
FaseTres::~FaseTres()
{
//Classe FaseAbstract remove o som da 'fase'
}
void FaseTres::configurar()
{
    tileSpace->setFrame(0,0,480,448);
    tileSpace->setTiles(15,222);
    tileSpace->setPixelTile(32,32);
    tileSpace->iniciarRandomico(3);

    soundSystem->musicManager->carregar("fase","data//som//003.ogg");
}
void FaseTres::iniciar()
{
    tileSpace->camera.setBottom();
    ListSpaceObstaculo::getInstance()->setLimite(10);

    ListSpaceObstaculo::OBSTACULO_ESFERA   = true;
    ListSpaceObstaculo::OBSTACULO_ASTEROID = true;
    ListSpaceObstaculo::OBSTACULO_MINA     = false;
    ListSpaceObstaculo::OBSTACULO_FURACAO  = false;

    GBF::Kernel::Sound::SoundSystem::getInstance()->musicManager->playInfinity("fase");

    nave = NaveFactory::criarNaveAliada(NaveFactory::ENTERPRISE);
}
void FaseTres::condicaoNavegandoFase()
{
    delay.acao--;
    if (delay.acao<=0){
        ListSpaceInimigo::getInstance()->adicionar(new NaveRomulana());
        delay.acao=80;
    }
}
void FaseTres::condicaoUnicaUltimoQuadro()
{
//Condição realizada apenas 1 vez, logo ao se chegar no ultimo quadro
//Ideal para gatilhos/triggers
    ListSpaceObstaculo::OBSTACULO_ESFERA   = false;
    ListSpaceObstaculo::OBSTACULO_ASTEROID = false;
    ListSpaceObstaculo::OBSTACULO_MINA     = false;
    ListSpaceObstaculo::OBSTACULO_FURACAO  = false;
}
std::string FaseTres::getMissaoCompleta()
{
	return "Fase 3";
}

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
#include "FaseDois.h"

FaseDois::FaseDois()
{
    delay.acao  = 10;
    delay.tiroA = 10;

    zona    = "fase_2_zona";
    missao  = "fase_2_missao";
    inimigo = "fase_2_inimigo";

    areaZona.left   =  59;
    areaZona.top    = 274;
    areaZona.bottom =  50;
    areaZona.right  = 518;
}
FaseDois::~FaseDois()
{
//Classe FaseAbstract remove o som da 'fase'
}
void FaseDois::configurar()
{
    tileSpace->setFrame(0,0,480,448);
    tileSpace->setTiles(15,168);
    tileSpace->setPixelTile(32,32);
    tileSpace->iniciarRandomico(3);

    soundSystem->musicManager->carregar("fase","data//som//002.ogg");
}
void FaseDois::iniciar()
{
    tileSpace->camera.setBottom();
    ListSpaceObstaculo::getInstance()->setLimite(10);

    ListSpaceObstaculo::OBSTACULO_ESFERA   = true;
    ListSpaceObstaculo::OBSTACULO_ASTEROID = false;
    ListSpaceObstaculo::OBSTACULO_MINA     = false;
    ListSpaceObstaculo::OBSTACULO_FURACAO  = false;

    GBF::Kernel::Sound::SoundSystem::getInstance()->musicManager->playInfinity("fase");

    nave = NaveFactory::criarNaveAliada(NaveFactory::ENTERPRISE);
}
void FaseDois::condicaoNavegandoFase()
{
    delay.acao--;
    if (delay.acao<=0){

        ListSpaceInimigo *lista = ListSpaceInimigo::getInstance();

        lista->adicionar(new NaveKlingonBirdPrev());
        lista->adicionar(new NaveKlingonBirdPrev());
        if (rand()%2==1){
            lista->adicionar(new NaveKlingonBirdPrev());
            lista->adicionar(new NaveKlingonBirdPrev());
        }
        delay.acao=330;
    }
}
void FaseDois::condicaoUnicaUltimoQuadro()
{
//Condição realizada apenas 1 vez, logo ao se chegar no ultimo quadro
//Ideal para gatilhos/triggers
    ListSpaceObstaculo::OBSTACULO_ESFERA = false;
}
std::string FaseDois::getMissaoCompleta()
{
	return "Fase 2";
}

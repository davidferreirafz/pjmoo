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
#include "FaseSeis.h"

FaseSeis::FaseSeis()
{
	delay.acao  = 10;
	delay.tiroA = 10;

    zona    = "fase_6_zona";
    missao  = "fase_6_missao";
    inimigo = "fase_6_inimigo";

    areaZona.left   =  59;
    areaZona.top    =  72;
    areaZona.bottom =  46;
    areaZona.right  = 518;
}
FaseSeis::~FaseSeis()
{
//Classe FaseAbstract remove o som da 'fase'
}
void FaseSeis::configurar()
{
    tileSpace->setFrame(0,0,480,448);
    tileSpace->setTiles(15,159);
    tileSpace->setPixelTile(32,32);
    tileSpace->iniciarRandomico(10);

    soundSystem->musicManager->carregar("fase","data//som//006.ogg");
}
void FaseSeis::iniciar()
{
    tileSpace->camera.setBottom();
    ListSpaceObstaculo::getInstance()->setLimite(8);

    ListSpaceObstaculo::OBSTACULO_ESFERA   = true;
    ListSpaceObstaculo::OBSTACULO_ASTEROID = false;
    ListSpaceObstaculo::OBSTACULO_MINA     = false;
    ListSpaceObstaculo::OBSTACULO_FURACAO  = true;

    soundSystem->musicManager->playInfinity("fase");

    nave = NaveFactory::criarNaveAliada(NaveFactory::ENTERPRISE_E);
}
void FaseSeis::condicaoNavegandoFase()
{
    delay.acao--;

    if (delay.acao<=0){
        delay.acao=200;

        int selecao=rand()%3;

        switch(selecao){
            case 0:
                ListSpaceInimigo::getInstance()->adicionar(new NaveCardassiana());
                ListSpaceInimigo::getInstance()->adicionar(new NaveCardassiana());
                break;
            case 1:
                ListSpaceInimigo::getInstance()->adicionar(new NaveCardassiana());
                ListSpaceInimigo::getInstance()->adicionar(new NaveCardassiana());
                ListSpaceInimigo::getInstance()->adicionar(new NaveCardassiana());
                break;
            case 2:
                ListSpaceInimigo::getInstance()->adicionar(new NaveCardassiana());
                ListSpaceInimigo::getInstance()->adicionar(new NaveCardassiana());
                ListSpaceInimigo::getInstance()->adicionar(new NaveCardassiana());
                ListSpaceInimigo::getInstance()->adicionar(new NaveCardassiana());
                ListSpaceInimigo::getInstance()->adicionar(new NaveCardassiana());
                break;
        }
    }
}
void FaseSeis::condicaoUnicaUltimoQuadro()
{
//Condição realizada apenas 1 vez, logo ao se chegar no ultimo quadro
//Ideal para gatilhos/triggers
    ListSpaceObstaculo::OBSTACULO_ESFERA   = false;
    ListSpaceObstaculo::OBSTACULO_ASTEROID = false;
    ListSpaceObstaculo::OBSTACULO_MINA     = false;
    ListSpaceObstaculo::OBSTACULO_FURACAO  = false;
}
std::string FaseSeis::getMissaoCompleta()
{
	return "Fase 6";
}


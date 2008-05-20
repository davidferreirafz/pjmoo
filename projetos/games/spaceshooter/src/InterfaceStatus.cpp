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
#include "InterfaceStatus.h"


InterfaceStatus* InterfaceStatus::instance=NULL;
InterfaceStatus* InterfaceStatus::getInstance()
{
    if (instance==NULL){
        instance = new InterfaceStatus();
    }
    return instance;
}
InterfaceStatus::InterfaceStatus()
{
    GBF::Imagem::SpriteFactory  *spriteFactory = new GBF::Imagem::SpriteFactory("tiles");

    warpBarra    = spriteFactory->criarSpriteItem(97,87,5,13,1,1);
    escudoBarra  = spriteFactory->criarSpriteItem(103,87,1,13,1,1);
    torpedoBarra = spriteFactory->criarSpriteItem(105,87,1,13,1,1);

    delete (spriteFactory);

    wsManager    = GBF::Kernel::Write::WriteManager::getInstance();
    soundSystem  = GBF::Kernel::Sound::SoundSystem::getInstance();

    inicializar();
}
InterfaceStatus::~InterfaceStatus()
{
    delete(warpBarra);
    delete(escudoBarra);
    delete(torpedoBarra);

    //UtilLog::getInstance()->inicializando("Removendo InterfaceStatus(Singleton)");
}
void InterfaceStatus::inicializar()
{
    tempo.setTempoOriginal(0);
    tempo.setUnidade(GBF::Kernel::Timer::TEMPO_SEGUNDO);
    tempo.setResetar();

    mostraTorpedo = true;
    mostraEscudo  = true;
}
void InterfaceStatus::desenharStatus(int totalWarp, int totalEscudo, int totalTorpedo)
{
    tempo.processar();

    if (totalTorpedo<4){
        if (tempo.getTempo()%2==0){
            mostraTorpedo = false;
        } else {
            mostraTorpedo = true;
        }
    }
    if (totalEscudo<10){
        if (totalEscudo<0){
            totalEscudo  = 0;
            mostraEscudo = true;
	} else if (tempo.getTempo()%2==0){
            mostraEscudo = false;
        } else {
            mostraEscudo = true;
        }
        if (tempo.getTempo()>=50){
            soundSystem->fxManager->play("alerta");
            tempo.setResetar();
        }
    }

//Desenho Itens
    for (int iw=0;((iw<totalWarp)&&(iw<13));iw++){
        warpBarra->desenhar(568+(5*iw),223);
    }
    wsManager->escrever("status",514,214,"%03i",totalWarp);

	if (mostraEscudo){
	    for (int ie=0;((ie<totalEscudo)&&(ie<65));ie++){
	       escudoBarra->desenhar(568+(1*ie),263);
	    }
	}
    wsManager->escrever("status",514,254,"%03i",totalEscudo);

    if (mostraTorpedo){
	    for (int it=0;((it<totalTorpedo)&&(it<65));it++){
	       torpedoBarra->desenhar(568+(1*it),303);
	    }
	}
    wsManager->escrever("status",514,294,"%03i",totalTorpedo);
}
void InterfaceStatus::desenharInformacoes(int pontos, int total, int distanciaRestante)
{
    wsManager->escrever("status",508,118,"%08i",pontos);
    wsManager->escrever("status",552,395,"%05i",total);
    wsManager->escrever("status",552,425,"%05i",distanciaRestante);
}




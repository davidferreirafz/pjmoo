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

    warpBarra    = spriteFactory->criarSpriteItem(0,34, 5,13,1,1);
    escudoBarra  = spriteFactory->criarSpriteItem(6,34, 1,13,1,1);
    torpedoBarra = spriteFactory->criarSpriteItem(8,34, 1,13,1,1);
    phaserLED    = spriteFactory->criarSpriteItem(0, 0,71, 8,3,4);
    torpedoLED   = spriteFactory->criarSpriteItem(0, 0,71, 8,3,4);

    phaserLED->animacao.setAutomatico(true);
    torpedoLED->animacao.setAutomatico(true);

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
    delete(phaserLED);
    delete(torpedoLED);

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
void InterfaceStatus::desenharStatus(int totalWarp, int totalEscudo, int totalTorpedo, bool phaserRecarregando, bool torpedoRecarregando)
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
        warpBarra->desenhar(565+(5*iw),230);
    }
    wsManager->escrever("status",512,221,"%03i",totalWarp);

	if (mostraEscudo){
	    for (int ie=0;((ie<totalEscudo)&&(ie<65));ie++){
	       escudoBarra->desenhar(565+(1*ie),275);
	    }
	}
    wsManager->escrever("status",512,266,"%03i",totalEscudo);

    if (mostraTorpedo){
	    for (int it=0;((it<totalTorpedo)&&(it<65));it++){
	       torpedoBarra->desenhar(565+(1*it),320);
	    }
	}

    wsManager->escrever("status",512,311,"%03i",totalTorpedo);

    if ((torpedoRecarregando)&&(totalTorpedo>0)){
        torpedoLED->desenhar(517,337);
    }

    if (phaserRecarregando){
        phaserLED->desenhar(517,395);
    }

}
void InterfaceStatus::desenharInformacoes(int pontos, int total, int distanciaRestante)
{
    wsManager->escrever("status",508,118,"%08i",pontos);
    //wsManager->escrever("status",552,395,"%05i",total);
    //wsManager->escrever("status",552,425,"%05i",distanciaRestante);
}




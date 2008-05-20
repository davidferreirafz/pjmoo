/***************************************************************************
 *   Copyright (C) 2005-2006 by David Ferreira                             *
 *   davidferreira@uol.com.br - davidferreira.fz@gmail.com                 *
 *   http://pjmoo.codigolivre.org.br                                       *
 *       http://davidferreira.fz.googlepages.com                           *
 *                                                                         *
 *   Este programa � um software livre; voc� pode redistribui-lo e/ou      *
 *   modifica-lo dentro dos termos da Licen�a P�blica Geral (GPL) GNU      *
 *   como publicada pela Funda��o do Software Livre (FSF); na vers�o 2 da  *
 *   Licen�a.                                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifndef _INTERFACESTATUS_H_
#define _INTERFACESTATUS_H_

#include <GBF/SpritePersonagem.h>
#include <GBF/ImageBufferManager.h>
#include <GBF/SpriteFactory.h>
#include <GBF/WriteManager.h>
#include <GBF/CronometroCrescente.h>
#include <GBF/SoundSystem.h>
#include <GBF/GraphicSystem.h>

class InterfaceStatus
{
public:
    /** Destrutor */
	virtual ~InterfaceStatus();
    /** Retorna a instancia da classe*/
	static InterfaceStatus* getInstance();
    /** Desenha interface e Status*/
    void desenharStatus(int totalWarp, int totalEscudo, int totalTorpedo);
    void desenharInformacoes(int pontos, int total, int distanciaRestante);
    /** Inicializa informa��es internar */
    void inicializar();

protected:
//Atributos
    GBF::Imagem::Sprite::SpriteItem * warpBarra;
    GBF::Imagem::Sprite::SpriteItem * escudoBarra;
    GBF::Imagem::Sprite::SpriteItem * torpedoBarra;

    GBF::Kernel::Timer::CronometroCrescente tempo;

	/** Instancia da classe (SINGLETON)*/
	static InterfaceStatus* instance;
    GBF::Kernel::Write::WriteManager * wsManager;


private:
    /** Construtor */
	InterfaceStatus();
	bool mostraEscudo;
	bool mostraTorpedo;
	GBF::Kernel::Sound::SoundSystem::SoundSystem * soundSystem;

};

#endif



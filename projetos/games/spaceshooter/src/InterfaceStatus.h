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
#ifndef _INTERFACESTATUS_H_
#define _INTERFACESTATUS_H_

#include <GBF/SpritePersonagem.h>
#include <GBF/GraphicSystemImageBufferManager.h>
#include <GBF/SpriteFactory.h>
#include <GBF/WriteSystemManager.h>
#include <GBF/TimerSystemCronometroCrescente.h>
#include <GBF/SoundSystem.h>

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
    /** Inicializa informações internar */
    void inicializar();

protected:
//Atributos
    SpriteItem* warpBarra;
    SpriteItem* escudoBarra;
    SpriteItem* torpedoBarra;
    TimerSystemCronometroCrescente tempo;

	/** Instancia da classe (SINGLETON)*/
	static InterfaceStatus* instance;
    WriteSystemManager* wsManager;


private:
    /** Construtor */
	InterfaceStatus();
	bool mostraEscudo;
	bool mostraTorpedo;
   	SoundSystem* soundSystem;

};

#endif



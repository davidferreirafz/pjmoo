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
#ifndef _TIROABSTRACT_H
#define _TIROABSTRACT_H

#include <GBF/GraphicSystemImageBufferManager.h>
#include <GBF/FrameLayerManager.h>
#include <GBF/SpriteFactory.h>
#include <GBF/PersonagemAutomatico.h>
#include "PathStrategy.h"

/** Potencia dos Tiros */
enum EnumTiroPotencia
{
    POTENCIA_NULL    = 0,
    POTENCIA_PHASER  = 2,
    POTENCIA_PLASMA  = 2,
    POTENCIA_TORPEDO = 4
};

/** Velocidade dos Tiros */
enum EnumTiroVelocidade
{
    VELOCIDADE_NULL    = 0,
    VELOCIDADE_PHASER  = 6,
    VELOCIDADE_PLASMA  = 8,
    VELOCIDADE_TORPEDO = 8
};

class TiroAbstract : public PersonagemAutomatico
{
public:
	//TiroAbstract(int X, int Y);
	TiroAbstract();
	virtual ~TiroAbstract();
	virtual  void acao(InputSystem* INPUT=NULL);
    int getPotencia();
protected:

	EnumTiroPotencia potencia;
	EnumTiroVelocidade velocidade;

	PathStrategy *path;

    static GraphicSystemImageBufferManager *gsImageBufferManager;
private:

};


#endif

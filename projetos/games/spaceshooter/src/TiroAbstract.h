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

#include <GBF/ImageBufferManager.h>
#include <GBF/LayerManager.h>
#include <GBF/GraphicSystem.h>
#include <GBF/SpriteFactory.h>
#include <GBF/Personagem.h>
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

class TiroAbstract : public Personagem::Personagem
{
public:
	TiroAbstract();
	virtual ~TiroAbstract();
	virtual  void acao(GBF::Kernel::Input::InputSystem* input=NULL);
    int getPotencia();
protected:

	EnumTiroPotencia potencia;
	EnumTiroVelocidade velocidade;

	PathStrategy *path;
private:

};


#endif

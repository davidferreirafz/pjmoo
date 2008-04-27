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
#ifndef _TIROPLASMAKLINGON_H
#define _TIROPLASMAKLINGON_H

#include "TiroPlasmaAbstract.h"
#include "PathUp.h"
#include "PathUpLeft.h"
#include "PathUpRight.h"
#include "PathDownLeft.h"
#include "PathDownRight.h"
#include "PathLeft.h"
#include "PathRight.h"
#include "PathDown.h"

typedef int PlasmaKlingon;


class TiroPlasmaKlingon : public TiroPlasmaAbstract
{
public:
	TiroPlasmaKlingon(int X, int Y,PlasmaKlingon tiro);
	virtual ~TiroPlasmaKlingon();

	static const PlasmaKlingon UP         = 0;
	static const PlasmaKlingon RIGHT      = 1;
	static const PlasmaKlingon DOWN       = 2;
	static const PlasmaKlingon LEFT       = 3;
	static const PlasmaKlingon UP_RIGHT   = 4;
	static const PlasmaKlingon UP_LEFT    = 5;
	static const PlasmaKlingon DOWN_RIGHT = 6;
	static const PlasmaKlingon DOWN_LEFT  = 7;

protected:
    void setTiro(PlasmaKlingon tiro);

private:

};

#endif

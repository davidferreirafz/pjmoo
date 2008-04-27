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
#ifndef _TIROPLASMAFE_H
#define _TIROPLASMAFE_H

#include "TiroPlasmaAbstract.h"
#include "PathUp.h"
#include "PathUpLeft.h"
#include "PathUpRight.h"
#include "PathDownLeft.h"
#include "PathDownRight.h"
#include "PathDown.h"


typedef int PlasmaFE;


class TiroPlasmaFE : public TiroPlasmaAbstract
{
public:
	TiroPlasmaFE(int X, int Y,PlasmaFE tiro);
	virtual ~TiroPlasmaFE();

	static const PlasmaFE UP         = 0;
	static const PlasmaFE UP_LEFT    = 1;
	static const PlasmaFE UP_RIGHT   = 2;
	static const PlasmaFE DOWN_LEFT  = 3;
	static const PlasmaFE DOWN_RIGHT = 4;
	static const PlasmaFE DOWN       = 5;

protected:
    void setTiro(PlasmaFE tiro);

private:

};

#endif

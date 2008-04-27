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
#ifndef _TIROPHASERFE_H
#define _TIROPHASERFE_H

#include "TiroPhaserAbstract.h"
#include "PathUp.h"
#include "PathDown.h"
#include "PathLeft.h"
#include "PathRight.h"
#include "PathDownLeft.h"
#include "PathDownRight.h"

typedef int PhaserPE;

class TiroPhaserFE : public TiroPhaserAbstract
{
public:
	TiroPhaserFE(int X, int Y,PhaserPE tiro);
	virtual ~TiroPhaserFE();

	static const PhaserPE UP    = 0;
	static const PhaserPE LEFT  = 1;
	static const PhaserPE DOWN  = 2;
	static const PhaserPE RIGHT = 3;
	static const PhaserPE DOWN_LEFT  = 4;
	static const PhaserPE DOWN_RIGHT = 5;

protected:
    void setTiro(PhaserPE tiro);

private:

};

#endif

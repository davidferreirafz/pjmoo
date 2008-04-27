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
#ifndef _TIROPHASERBORG_H
#define _TIROPHASERBORG_H

#include "TiroPhaserAbstract.h"
#include "PathUp.h"
#include "PathDown.h"
#include "PathLeft.h"
#include "PathRight.h"


typedef int PhaserBorg;

class TiroPhaserBorg : public TiroPhaserAbstract
{
public:
	TiroPhaserBorg(int X, int Y,PhaserBorg tiro);
	virtual ~TiroPhaserBorg();

	static const PhaserBorg UP    = 0;
	static const PhaserBorg LEFT  = 1;
	static const PhaserBorg DOWN  = 2;
	static const PhaserBorg RIGHT = 3;

protected:
    void setTiro(PhaserBorg tiro);

private:

};

#endif

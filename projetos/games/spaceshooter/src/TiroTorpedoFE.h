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
#ifndef _TIROTORPEDOUP_H
#define _TIROTORPEDOUP_H

#include "TiroTorpedoAbstract.h"
#include "PathUp.h"
#include "PathUpLeft.h"
#include "PathUpRight.h"
#include "PathDown.h"

typedef int TorpedoFE;

class TiroTorpedoFE : public TiroTorpedoAbstract
{
public:
	TiroTorpedoFE(int X, int Y,TorpedoFE tiro);
	virtual ~TiroTorpedoFE();

	static const TorpedoFE UP         = 0;
	static const TorpedoFE UP_LEFT    = 1;
	static const TorpedoFE UP_RIGHT   = 2;
	static const TorpedoFE DOWN       = 3;

protected:
    void setTiro(TorpedoFE tiro);


private:

};

#endif

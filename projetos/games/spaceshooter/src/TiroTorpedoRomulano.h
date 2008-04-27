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
#ifndef _TIROTORPEDOUPROMULANO_H
#define _TIROTORPEDOUPROMULANO_H

#include "TiroTorpedoAbstract.h"
#include "PathUp.h"
#include "PathLeft.h"
#include "PathRight.h"
#include "PathDown.h"

typedef int TorpedoRomulano;

class TiroTorpedoRomulano : public TiroTorpedoAbstract
{
public:
	TiroTorpedoRomulano(int X, int Y,TorpedoRomulano tiro);
	virtual ~TiroTorpedoRomulano();

	static const TorpedoRomulano UP     = 0;
	static const TorpedoRomulano LEFT   = 1;
	static const TorpedoRomulano RIGHT  = 2;
	static const TorpedoRomulano DOWN   = 3;

protected:
    void setTiro(TorpedoRomulano tiro);


private:

};

#endif

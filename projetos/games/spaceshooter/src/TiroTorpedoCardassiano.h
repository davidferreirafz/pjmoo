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
#ifndef _TIROTORPEDOUPCARDASSIANO_H
#define _TIROTORPEDOUPCARDASSIANO_H

#include "TiroTorpedoAbstract.h"
#include "PathUp.h"
#include "PathLeft.h"
#include "PathRight.h"
#include "PathDown.h"

typedef int TorpedoCardassiano;

class TiroTorpedoCardassiano : public TiroTorpedoAbstract
{
public:
	TiroTorpedoCardassiano(int X, int Y,TorpedoCardassiano tiro);
	virtual ~TiroTorpedoCardassiano();

	static const TorpedoCardassiano UP     = 0;
	static const TorpedoCardassiano LEFT   = 1;
	static const TorpedoCardassiano RIGHT  = 2;
	static const TorpedoCardassiano DOWN   = 3;

protected:
    void setTiro(TorpedoCardassiano tiro);


private:

};

#endif

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
#ifndef _FASEFACTORY_H_
#define _FASEFACTORY_H_

#include "FaseAbstract.h"
#include "FaseUm.h"
#include "FaseDois.h"
#include "FaseTres.h"
#include "FaseQuatro.h"
#include "FaseCinco.h"
#include "FaseSeis.h"
#include "FaseSete.h"

class FaseFactory
{
public:
	static FaseAbstract* criarFase( int numero );
	static bool isProximaFase(int faseAtual);
private:
	static const int MAX_FASE = 7;
};

#endif

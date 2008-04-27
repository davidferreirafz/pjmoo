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
#ifndef _NAVEFACTORY_H_
#define _NAVEFACTORY_H_

#include "NaveAliado.h"
#include "NaveAuxiliar.h"
#include "NaveEnterpriseE.h"
#include "NaveEnterprise.h"
#include "NaveVoyager.h"


class NaveFactory
{
public:
	static const int AUXILIAR     = 1;
	static const int ENTERPRISE   = 2;
	static const int VOYAGER      = 3;
	static const int ENTERPRISE_E = 4;

	static NaveAliado* criarNaveAliada( int tipoNave );


};

#endif

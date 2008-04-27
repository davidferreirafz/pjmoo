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
#ifndef _PATHFACTORY_H_
#define _PATHFACTORY_H_

#include "PathStrategy.h"
#include "PathDown.h"
#include "PathDownLeft.h"
#include "PathDownRight.h"
#include "PathLeft.h"
#include "PathRight.h"
#include "PathUp.h"
#include "PathUpLeft.h"
#include "PathUpRight.h"

enum EnumPathTipo
{
    PATH_DOWN,
    PATH_DOWN_LEFT,
    PATH_DOWN_RIGHT,
    PATH_LEFT,
    PATH_RIGHT,
    PATH_UP,
    PATH_UP_LEFT,
    PATH_UP_RIGHT
};

class PathFactory
{
public:
	static PathStrategy* criar(EnumPathTipo ePathTipo);
	
};

#endif


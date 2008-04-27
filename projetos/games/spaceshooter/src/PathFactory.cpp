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
#include "PathFactory.h"

PathStrategy* PathFactory::criar(EnumPathTipo ePathTipo)
{
    PathStrategy* path = NULL;
    
    switch(ePathTipo){
        case PATH_DOWN:
            path = new PathDown();
            break;
        case PATH_DOWN_LEFT:
            path = new PathDownLeft();
            break;
        case PATH_DOWN_RIGHT:
            path = new PathDownRight();
            break;
        case PATH_LEFT:
            path = new PathLeft();
            break;
        case PATH_RIGHT:
            path = new PathRight();
            break;
        case PATH_UP:
            path = new PathUp();
            break;
        case PATH_UP_LEFT:
            path = new PathUpLeft();
            break;
        case PATH_UP_RIGHT:
            path = new PathUpRight();
            break;
    }
    return path;
}

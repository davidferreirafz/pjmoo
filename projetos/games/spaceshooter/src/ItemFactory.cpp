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
#include "ItemFactory.h"

ItemAbstract* ItemFactory::criar(EnumItem eItem)
{
    ItemAbstract *item = NULL;
    
    switch(eItem){
        case ITEM_VELOCIDADE:
                item = new ItemVelocidade();
            break;
        case ITEM_ARMA:
                item = new ItemArma();
            break;
        case ITEM_ESCUDO:
                item = new ItemEscudo();
            break;
    }
    
    return item;
}


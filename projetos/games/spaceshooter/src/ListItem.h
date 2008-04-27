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
#ifndef _LISTITEM_H_
#define _LISTITEM_H_

#include <GBF/WriteSystemManager.h>

#include "ListItem.h"
#include "ListSpaceAbstract.h"
#include "ItemAbstract.h"

class ListItem : public ListSpaceAbstract
{
public:
	virtual ~ListItem();
	
	static ListItem* getInstance();

	void adicionar(ItemAbstract* item);	
    ItemAbstract* getItem(int indice);
    
protected:
    WriteSystemManager *wsManager;
	ListItem();
	static ListItem* instance;
	void desenhar();
	
};

#endif 


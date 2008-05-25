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
#include "ListItem.h"

ListItem* ListItem::instance=NULL;
ListItem* ListItem::getInstance()
{
	if (instance == NULL){
		instance = new ListItem();
	}
	return instance;
}
ListItem::~ListItem()
{
}
ListItem::ListItem()
{
    wsManager = GBF::Kernel::Write::WriteManager::getInstance();
}
void ListItem::adicionar(ItemAbstract* item)
{
    if (item!=NULL){
        lista.push_back(item);
   	}
}
ItemAbstract* ListItem::getItem(int indice)
{
	return (ItemAbstract*)lista[indice];
}
void ListItem::desenhar()
{
    ListSpaceAbstract::desenhar();

    if (lista.size()>0){
        for (unsigned int i=0;i<lista.size();i++){
            ItemAbstract* item=(ItemAbstract*)lista[i];
            wsManager->escreverLocalizado("texto",10,10+(i*20),item->getHelp().c_str());
        }

    }
}



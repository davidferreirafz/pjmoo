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
#include "ListSpaceAbstract.h"

ListSpaceAbstract::ListSpaceAbstract()
{
}
ListSpaceAbstract::~ListSpaceAbstract()
{
}
void ListSpaceAbstract::desenhar()
{
    if (!lista.empty()){
        remover();
        ListPersonagem::desenhar();
    }
}
//Remove mortos
void ListSpaceAbstract::remover()
{
	for (int i=lista.size()-1; i>=0; i--){
		if (lista[i]!=NULL){
			if (lista[i]->isAtivo()==false){
				delete lista[i];
				lista[i]=NULL;
				lista.erase(lista.begin()+i);
			}
		}
	}
}


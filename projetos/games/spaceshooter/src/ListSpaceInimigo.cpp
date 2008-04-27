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
#include "ListSpaceInimigo.h"

ListSpaceInimigo* ListSpaceInimigo::instance=NULL;

ListSpaceInimigo::ListSpaceInimigo()
{
	limite=0;
}
ListSpaceInimigo::~ListSpaceInimigo()
{
//	UtilLog::getInstance()->inicializando("Removendo ListSpaceInimigo (Singleton)");
}
ListSpaceInimigo* ListSpaceInimigo::getInstance()
{
		if (instance == NULL){
			instance = new ListSpaceInimigo();		
		}
		return instance;
}
void ListSpaceInimigo::colisao(SpaceObject* alvo)
{
	NaveInimigo *nave=NULL;
    
    for (int iNave=0; iNave<size(); iNave++){
        nave=(NaveInimigo*)getPersonagem(iNave);
        if ((nave!=NULL)&&(nave->isVivo())){
            if ((alvo!=NULL)&&(alvo->isVivo())){
				if (nave->isColisao(alvo)){
                    nave->choque(1);
					alvo->choque(1);
 					break;
				}                    
            }
        }
    }
}




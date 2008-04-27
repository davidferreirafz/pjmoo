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
#ifndef _SPACEOBJECT_H_
#define _SPACEOBJECT_H_

#include <GBF/GBF_define.h>
#include <GBF/PersonagemAutomatico.h>

class SpaceObject: public PersonagemAutomatico
{
protected:
	static Area area;
	
public:
	static void setArea(Area area);
	virtual void choque(int forca) = 0;
	virtual int tipoClasse();
	virtual bool tipoClasse(int tipo);
	
};

#endif



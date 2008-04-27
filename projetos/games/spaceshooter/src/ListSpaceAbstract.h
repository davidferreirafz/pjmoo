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
#ifndef _LISTSPACEABSCTRACT_H
#define _LISTSPACEABSCTRACT_H

#include <GBF/ListPersonagemAutomaticoAbstract.h>



class ListSpaceAbstract : public ListPersonagemAutomaticoAbstract
{
public:
    /** Construtor */
    ListSpaceAbstract();
    /** Destrutor */
    virtual ~ListSpaceAbstract();
    /** Remove mortos e desenha os ativos */
	virtual void executar();

protected:
    /** Remove personagens n�o ativo(mortos) */
	void removerMorto();


private:

};

#endif

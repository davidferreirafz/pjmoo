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
#ifndef _ITEMABSTRACT_H_
#define _ITEMABSTRACT_H_

#include <GBF/SpriteFactory.h>
#include <GBF/ImageBufferManager.h>

#include "SpaceObject.h"
#include "PathFactory.h"
#include "PathStrategy.h"

enum EnumItem
{
	ITEM_ESCUDO     = 0,
	ITEM_ARMA       = 1,
    ITEM_VELOCIDADE = 2
};

class ItemAbstract : public SpaceObject
{
public:
    /** Destrutor */
	virtual ~ItemAbstract();
	/** Construtor */
	ItemAbstract();
    /** Retorna o tipo de Item*/
    virtual EnumItem getTipo()=0;
    /** Retorna mensagem sobre o item*/
    virtual std::string getHelp()=0;
    int getBonus();
    virtual void acao(GBF::Kernel::Input::InputSystem * INPUT=NULL);

protected:
	int bonus;
	int velocidade;
	PathStrategy *path;
    void selecionarPosicao();

private:
    /** Implementado devido obrigatoriedade exigida por SpaceObject*/
    void choque(int forca);
};

#endif



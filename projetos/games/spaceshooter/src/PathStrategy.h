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
#ifndef _PATHSTRATEGY_H
#define _PATHSTRATEGY_H

#include <GBF/GBF_define.h>
#include <GBF/FrameLayerManager.h>

class PathStrategy
{
public:
    /** Construtor */
	PathStrategy();
    /** Destrutor */
	virtual ~PathStrategy();

	/** Implementa o algoritmo de movimentação.
    OBs.: Retorna verdadeiro se atingiu o limite de movimentação */
	virtual bool mover(int velocidade,Ponto *posicao,Dimensao dimensao)=0;	
		
protected:
	Area area;
	
};

#endif

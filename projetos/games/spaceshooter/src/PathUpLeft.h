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
#ifndef PATHUPLEFT_H
#define PATHUPLEFT_H

#include "PathStrategy.h"

class PathUpLeft : public PathStrategy
{
public:
	/** Construtor */
	PathUpLeft();
	/** Destrutor */
	virtual ~PathUpLeft();
	
	/** Implementa o algoritmo de movimentação.
    OBs.: Retorna verdadeiro se atingiu o limite de movimentação */
	bool mover(int velocidade,Ponto *posicao,Dimensao dimensao);	
};

#endif

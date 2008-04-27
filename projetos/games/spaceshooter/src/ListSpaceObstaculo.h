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
#ifndef _LISTSPACEOBSTACULO_H
#define _LISTSPACEOBSTACULO_H

#include <GBF/UtilLog.h>

#include "ListSpaceAbstract.h"
#include "ObstaculoAbstract.h"
#include "ObstaculoMina.h"
#include "ObstaculoFuracao.h"
#include "ObstaculoAsteroid.h"
#include "ObstaculoEsfera.h"

#include "NaveAbstract.h"



class ListSpaceObstaculo : public ListSpaceAbstract
{
public:
	static bool OBSTACULO_ESFERA;
	static bool OBSTACULO_ASTEROID;
	static bool OBSTACULO_MINA;
	static bool OBSTACULO_FURACAO;

	
    /** Destrutor */
    virtual ~ListSpaceObstaculo();
    /** Instancia*/
    static ListSpaceObstaculo* getInstance();
    
    void adicionar(int quantidade);
    void setLimite(int maximo);
    void acao();
    
    void criar();   
    
    void colisao(NaveAbstract* nave);
    
protected:
    static ListSpaceObstaculo* instance;
    int limite;

private:
    ListSpaceObstaculo();


};

#endif



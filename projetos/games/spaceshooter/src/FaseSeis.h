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
#ifndef _FASESEIS_H_
#define _FASESEIS_H_


#include "FaseAbstract.h"
#include "ListSpaceObstaculoNeutro.h"
#include "ListSpaceInimigo.h"
#include "NaveCardassiana.h"


class FaseSeis : public FaseAbstract
{
private:
	TypeDelay delay;

public:
    /** Construtor */
    FaseSeis();
    /** Destrutor */
    virtual ~FaseSeis();

    void iniciar();   
    void configurar();
    /** Informa se passou de fase*/
    bool isTerminou();
    std::string getMissaoCompleta();
    
protected:	
    /** Condi��o executada durante toda a fase */
    void condicaoNavegandoFase();
    /** Condi��o executada apenas na ultima tela*/
    void condicaoUnicaUltimoQuadro();
};

#endif

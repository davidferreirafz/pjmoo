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
#ifndef _FASEDOIS_H
#define _FASEDOIS_H


#include "FaseAbstract.h"
#include "ListSpaceInimigo.h"
#include "NaveKlingonBirdPrev.h"

class FaseDois : public FaseAbstract
{
public:
    /** Construtor */
    FaseDois();
    /** Destrutor */
    virtual ~FaseDois();
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

private:
    TypeDelay delay;
};

#endif

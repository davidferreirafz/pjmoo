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
#ifndef _FASEUM_H
#define _FASEUM_H

#include <GBF/WriteSystemManager.h>
#include <GBF/TimerSystemCronometroCrescente.h>

#include "FaseAbstract.h"
#include "ListSpaceObstaculo.h"
#include "ListSpaceInimigo.h"

class FaseUm : public FaseAbstract
{
public:
    /** Construtor */
    FaseUm();
    /** Destrutor */
    virtual ~FaseUm();
    void configurar();
    void iniciar();
    /** Informa se passou de fase*/
    bool isTerminou();

protected:
    /** Condição executada durante toda a fase */
    void condicaoNavegandoFase();
    /** Condição executada apenas na ultima tela*/
    void condicaoUnicaUltimoQuadro();
    void ganchoUltimoQuadro();
    std::string getMissaoCompleta();

private:
    WriteSystemManager *wsManager;
    TimerSystemCronometroCrescente tempoDica;
    int dicaSelecao;
};

#endif

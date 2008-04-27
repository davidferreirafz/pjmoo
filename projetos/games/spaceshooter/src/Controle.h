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
#ifndef _CONTROLE_H_
#define _CONTROLE_H_
#include <GBF/UtilLog.h>

#include "ListSpaceInimigo.h"
#include "ListSpaceObstaculo.h"
#include "ListSpaceObstaculoNeutro.h"
#include "FaseAbstract.h"
#include "FaseFactory.h"
#include "Placar.h"


class Controle
{

public:
    /** Construtor*/
    Controle();
    /** Destrutor*/
    virtual ~Controle();
    TopSystemRecorde novoRecorde();

    void novoJogo();
    bool carregarFase();
    void jogoExecutando(InputSystem* input);
    void faseFinalizada();
    bool isGameOver();
    bool isFaseFinalizada();
    Area getFaseAreaZona();
    void inicializarFase();
    const char* getZona();
    const char* getMissao();
    const char* getInimigo();

protected:
    /** Referencia ao objeto singleton Placar*/
    Placar *placar;

private:
    FaseAbstract* fase;
    int numeroFase;
    void mudarFase();
    void limparList();
};

#endif

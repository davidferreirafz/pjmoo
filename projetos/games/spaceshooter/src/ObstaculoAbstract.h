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
#ifndef _OBSTACULOABSTRACT_H
#define _OBSTACULOABSTRACT_H

#include <GBF/GraphicSystemImageBufferManager.h>
#include <GBF/SpriteFactory.h>
#include <GBF/PersonagemAutomatico.h>
#include <GBF/SoundSystem.h>

#include "spaceshoot_define.h"
#include "PathFactory.h"
#include "SpaceObject.h"


class ObstaculoAbstract : public SpaceObject
{
public:
    /** Construtor */
    ObstaculoAbstract();
    /** Destrutor */
    virtual ~ObstaculoAbstract();
	static void setVelocidadeBase(int velocidadeBase);
    void setVivo(bool VALOR);
    void desenhar();
    void acao(InputSystem* INPUT=NULL);
    int getResistencia();
    int getDanos();
    void choque(int forca);

protected:
    int velocidade;
    int resistencia;
    int danos;

	PathStrategy *path;

    int getVelocidadeBase();
	virtual void selecionarPosicao();

private:
	static int velocidadeBase;



};

#endif


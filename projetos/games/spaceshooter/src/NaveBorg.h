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
#ifndef _NAVEBORG_H
#define _NAVEBORG_H

#include "NaveInimigo.h"
#include "NaveMiniBorg.h"
#include "ListSpaceInimigo.h"
#include "TiroCanhaoBorg.h"
#include "EfeitoFogosDeArtificio.h"

class NaveBorg : public NaveInimigo
{
public:
	NaveBorg();
	virtual ~NaveBorg();
    void acao(GBF::Kernel::Input::InputSystem * input=NULL);
    /** Desenha a nave na tela*/
    void desenhar();
	void choque(int forca);
    virtual void setVivo(bool VALOR);

protected:
	void dispararPhaser();
	void dispararTorpedo();

private:
    GBF::Kernel::Graphic::GFX * gsGFX;


};

#endif

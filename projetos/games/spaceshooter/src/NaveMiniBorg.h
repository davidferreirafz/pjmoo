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
#ifndef _NAVEMINIBORG_H
#define _NAVEMINIBORG_H

#include "NaveInimigo.h"
#include "TiroPhaserBorg.h"
#include "NaveBorg.h"


class NaveMiniBorg : public NaveInimigo
{
public:
    NaveMiniBorg();
    virtual ~NaveMiniBorg();

protected:
    void dispararPhaser();
    void dispararTorpedo();

private:
    void posicionar(int x, int y, GBF::Imagem::Sprite::Direcao direcaoOriginal);

    friend class NaveBorg;
};

#endif

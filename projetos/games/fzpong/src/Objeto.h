///***************************************************************************
// *   FZPong <Game - Pong Clone>                                            *
// *   Copyright (C) 2007 by David Ferreira - FZ                             *
// *   davidferreira.fz@gmail.com - http://pjmoo.sourceforge.net             *
// ***************************************************************************
// *   Este programa � software livre; voc� pode redistribu�-lo e/ou         *
// *   modific�-lo sob os termos da Licen�a P�blica Geral GNU, conforme      *
// *   publicada pela Free Software Foundation; tanto a vers�o 2 da          *
// *   Licen�a como (a seu crit�rio) qualquer vers�o mais nova.              *
// ***************************************************************************
// *   This program is free software; you can redistribute it and/or modify  *
// *   it under the terms of the GNU General Public License as published by  *
// *   the Free Software Foundation; either version 2 of the License, or     *
// *   (at your option) any later version.                                   *
// *                                                                         *
// *   You should have received a copy of the GNU General Public License     *
// *   along with this program; if not, write to the                         *
// *   Free Software Foundation, Inc.,                                       *
// *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
// ***************************************************************************/
#ifndef _OBJETO_H
#define _OBJETO_H

#include <GBF/ImageBase.h>

#include <GBF/SoundSystem.h>

#include <GBF/Personagem.h>
#include <GBF/SoundSystemUtility.h>

class Objeto : public Personagem::Personagem, public GBF::Kernel::Sound::SoundSystemUtility
{
  public:
    Objeto();

    virtual ~Objeto();

    static void setArea(GBF::Area area);


  protected:
    GBF::Area getAreaTela();

//    static GBF::Kernel::Sound::SoundSystem * soundSystem;


  private:
    static GBF::Area areaTela;

    int alturaPedra;

};
#endif

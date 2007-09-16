///***************************************************************************
// *   Pancada <Game - Boxing Clone>                                         *
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

#ifndef _USERINTERFACEVISUALIMAGEM_H
#define _USERINTERFACEVISUALIMAGEM_H

#include <GBF/GBF_define.h>

#include "UserInterfaceVisual.h"
#include <GBF/FrameLayer.h>

#include <GBF/GraphicSystemImageBufferManager.h>

#include <GBF/SpriteFactory.h>


enum UserInterfaceVisualTipoBackground {
  BACKGROUND_LINES =0,
  BACKGROUND_RINGS =1,
  BACKGROUND_CHESS =2,
  BAKCGROUND_SQUARE =3
};
class UserInterfaceVisualImagem : public UserInterfaceVisual
{
  public:
    UserInterfaceVisualImagem();

    UserInterfaceVisualImagem(const UserInterfaceVisualImagem & base);

    virtual ~UserInterfaceVisualImagem();

    //Aplica o efeito visual
    virtual void aplicar(const Ponto & posicao, const Dimensao & dimensao);

    //Desenha o EstiloVisual do Componente
    virtual void desenhar();

    virtual UserInterfaceVisual * clone();

    //Define o estilo de background a ser utilizado
    void setTipoBackground(UserInterfaceVisualTipoBackground tipo);


  protected:
    FrameLayer * background;

    static GraphicSystemImageBufferManager * gsImageBufferManager;

    UserInterfaceVisualTipoBackground tipoBackground;

};
#endif

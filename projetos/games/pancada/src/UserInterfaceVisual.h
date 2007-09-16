///***************************************************************************
// *   Pancada <Game - Boxing Clone>                                         *
// *   Copyright (C) 2007 by David Ferreira - FZ                             *
// *   davidferreira.fz@gmail.com - http://pjmoo.sourceforge.net             *
// ***************************************************************************
// *   Este programa é software livre; você pode redistribuí-lo e/ou         *
// *   modificá-lo sob os termos da Licença Pública Geral GNU, conforme      *
// *   publicada pela Free Software Foundation; tanto a versão 2 da          *
// *   Licença como (a seu critério) qualquer versão mais nova.              *
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

#ifndef _USERINTERFACEVISUAL_H
#define _USERINTERFACEVISUAL_H

#include <GBF/GBF_define.h>

#include <GBF/UtilColor.h>

#include <GBF/GraphicSystemGFX.h>


class UserInterfaceVisual
{
  public:
    UserInterfaceVisual();

    UserInterfaceVisual(const UserInterfaceVisual & base);

    virtual ~UserInterfaceVisual();

    void setCorBorda(const CorPaleta & r, const CorPaleta & g, const CorPaleta & b);

    //Aplica o efeito visual
    virtual void aplicar(const Ponto & posicao, const Dimensao & dimensao);

    //Desenha o EstiloVisual do Componente
    virtual void desenhar() = 0;

    virtual UserInterfaceVisual * clone() = 0;


  protected:
    RGB corBorda;

    Ponto posicao;

    Dimensao dimensao;

    static GraphicSystemGFX * gsGFX;

};
#endif

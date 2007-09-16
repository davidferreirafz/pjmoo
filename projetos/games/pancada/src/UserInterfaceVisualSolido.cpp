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

#include "UserInterfaceVisualSolido.h"

UserInterfaceVisualSolido::UserInterfaceVisualSolido() 
{
}
UserInterfaceVisualSolido::UserInterfaceVisualSolido(const UserInterfaceVisualSolido & base):UserInterfaceVisual(base) 
{
    corFundo=base.corFundo;
}
UserInterfaceVisualSolido::~UserInterfaceVisualSolido() 
{
}
void UserInterfaceVisualSolido::setCorFundo(const CorPaleta & r, const CorPaleta & g, const CorPaleta & b) 
{
    corFundo.r=r;
    corFundo.g=g;
    corFundo.b=b;
}
//Desenha o EstiloVisual do Componente
void UserInterfaceVisualSolido::desenhar() 
{
    gsGFX->setColor(corFundo.r,corFundo.g,corFundo.b);
    gsGFX->retanguloPreenchido(posicao.x,posicao.y,dimensao.w,dimensao.h);

    gsGFX->setColor(corBorda.r,corBorda.g,corBorda.b);
    gsGFX->retangulo(posicao.x,posicao.y,dimensao.w,dimensao.h);
}
UserInterfaceVisual * UserInterfaceVisualSolido::clone() 
{
   return new UserInterfaceVisualSolido(*this);
}

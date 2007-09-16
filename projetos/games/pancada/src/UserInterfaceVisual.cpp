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

#include "UserInterfaceVisual.h"

UserInterfaceVisual::UserInterfaceVisual() 
{
    if (gsGFX==NULL){
        gsGFX = GraphicSystemGFX::getInstance();
    }

}
UserInterfaceVisual::UserInterfaceVisual(const UserInterfaceVisual & base) 
{
    posicao  = base.posicao;
    dimensao = base.dimensao;
    corBorda = base.corBorda;
}
UserInterfaceVisual::~UserInterfaceVisual() 
{
}
void UserInterfaceVisual::setCorBorda(const CorPaleta & r, const CorPaleta & g, const CorPaleta & b) 
{
    corBorda.r=r;
    corBorda.g=g;
    corBorda.b=b;
}
//Aplica o efeito visual
void UserInterfaceVisual::aplicar(const Ponto & posicao, const Dimensao & dimensao) 
{
    this->dimensao=dimensao;
    this->posicao=posicao;
}
GraphicSystemGFX * UserInterfaceVisual::gsGFX =NULL;


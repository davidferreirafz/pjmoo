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

#include "UserInterfaceVisualImagem.h"

UserInterfaceVisualImagem::UserInterfaceVisualImagem() 
{
    if (gsImageBufferManager==NULL){
        gsImageBufferManager = GraphicSystemImageBufferManager::getInstance();
    }
}
UserInterfaceVisualImagem::UserInterfaceVisualImagem(const UserInterfaceVisualImagem & base):UserInterfaceVisual(base) 
{
    background=base.background;
}
UserInterfaceVisualImagem::~UserInterfaceVisualImagem() 
{
    if (background!=NULL){
        delete(background);
    }
}
//Aplica o efeito visual
void UserInterfaceVisualImagem::aplicar(const Ponto & posicao, const Dimensao & dimensao) 
{
    UserInterfaceVisual::aplicar(posicao,dimensao);
    SpriteFactory *spriteFactory = new SpriteFactory(gsImageBufferManager->getImageBuffer("gbf-window-background"));
    background = spriteFactory->criarFrameLayer(0,0,10,10);
    delete(spriteFactory);

    if (background!=NULL){
        background->setFrame(posicao.x,posicao.y,dimensao.w,dimensao.h);
        background->setTiles((dimensao.w/10),(dimensao.h/10));
        background->setPixelTile(10,10);
        background->iniciarCom(0);
    }
}
//Desenha o EstiloVisual do Componente
void UserInterfaceVisualImagem::desenhar() 
{
    if (background!=NULL){
        background->desenhar();
    }
    gsGFX->setColor(corBorda.r,corBorda.g,corBorda.b);
    gsGFX->retangulo(posicao.x,posicao.y,dimensao.w,dimensao.h);
}
UserInterfaceVisual * UserInterfaceVisualImagem::clone() 
{
   return new UserInterfaceVisualImagem(*this);
}
//Define o estilo de background a ser utilizado
void UserInterfaceVisualImagem::setTipoBackground(UserInterfaceVisualTipoBackground tipo) 
{
    tipoBackground=tipo;
}
GraphicSystemImageBufferManager * UserInterfaceVisualImagem::gsImageBufferManager =NULL;


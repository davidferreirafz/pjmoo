//***************************************************************************
//  Pancada <Game - Boxing Style>
//  Copyright (C) 2007 by David Ferreira - FZ
//  davidferreira.fz@gmail.com - http://pjmoo.sourceforge.net 
//***************************************************************************
//    Este programa é software livre; você pode redistribuí-lo e/ou
//    modificá-lo sob os termos da Licença Pública Geral GNU, conforme
//    publicada pela Free Software Foundation; tanto a versão 2 da 
//    Licença como (a seu critério) qualquer versão mais nova.
//***************************************************************************
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or 
//    (at your option) any later version.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the
//    Free Software Foundation, Inc.,                                       
//    59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//***************************************************************************
#include "StatusTempo.h"

StatusTempo::StatusTempo() 
{

    GraphicSystem  *graphicSystem = GraphicSystem::getInstance();
    SpriteFactory  *spriteFactory = new SpriteFactory(graphicSystem->imageBufferManager->getImageBuffer("interface"));

    painel = spriteFactory->criarSpriteItem(0,265,92,40,1,1);

    delete(spriteFactory);
}
StatusTempo::~StatusTempo() 
{

    //dtor
}
void StatusTempo::desenhar(int tempo) 
{
    painel->desenhar(274,0);
    wsManager->escrever("kiloton24",298,11,"%02d",tempo);
}

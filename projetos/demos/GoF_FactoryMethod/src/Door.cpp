//***************************************************************************
//  UML <Demo - GoF - Designer Patterns>
//  Copyright (C) 2007 by David Ferreira - FZ
//  davidferreira.fz@gmail.com - http://pjmoo.wiki.sourceforge.net/GoF
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
#include "Door.h"

Door::Door(Room * room1, Room * room2) 
{
    SpriteFactory  *spriteFactory = new SpriteFactory(graphicSystem->imageBufferManager->getImageBuffer("tiles"));
    sprite = spriteFactory->criarSpriteItem(64,0,32,32,1,1);

    delete(spriteFactory);

    room[0]=room1;
    room[1]=room2;
}
Door::~Door() 
{
    if (room[0]){
        Direction d = room[0]->getDirection(this);
        room[0]->setSide(d,NULL);
    }

    if (room[1]){
        Direction d = room[1]->getDirection(this);
        room[1]->setSide(d,NULL);
    }

    room[0]=NULL;
    room[1]=NULL;
}
void Door::enter() 
{
}
Room * Door::otherSideFrom(Room * theRoom) 
{
    if (theRoom==room[0]){
        return room[1];
    } else if (theRoom==room[1]){
        return room[0];
    } else {
        return NULL;
    }
}

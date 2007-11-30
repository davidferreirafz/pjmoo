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
#include "Room.h"

Room::Room(int number)
{
    roomNumber = number;

    SpriteFactory  *spriteFactory = new SpriteFactory(graphicSystem->imageBufferManager->getImageBuffer("tiles"));
    sprite = spriteFactory->criarSpriteItem(32,0,32,32,1,1);

    delete(spriteFactory);
}
Room::Room(const Room & source)
{
    sides[North] = source.sides[North];
    sides[East]  = source.sides[East];
    sides[South] = source.sides[South];
    sides[West]  = source.sides[West];
}
Room::~Room()
{
    for (int i=0; i<4; i++){
        if (sides[i]){
            delete(sides[i]);
        }
    }
}
void Room::enter()
{
}
void Room::draw(int x, int y)
{
    if (sprite){
        sprite->desenhar(x,y);
    }

    if (sides[North]){
        sides[North]->draw(x,y-32);
    }

    if (sides[East]){
        sides[East]->draw(x+32,y);
    }

    if (sides[South]){
        sides[South]->draw(x,y+32);
    }

    if (sides[West]){
        sides[West]->draw(x-32,y);
    }
}
void Room::setSide(Direction direction, MapSite * map)
{
    sides[direction]=map;
}
MapSite * Room::getSide(Direction direction) const
{
    return sides[direction];
}
Direction Room::getDirection(MapSite * map)
{
    Direction direction = INVALID;

    for (int i=0; i<4; i++){
        if (sides[i]==map){
            direction = (Direction) i;
            break;
        }
    }

    return direction;
}
int Room::getNumber()
{
    return roomNumber;
}
Room * Room::clone() const
{
    return new Room(*this);
}

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
#include "StandardMazeBuilder.h"

StandardMazeBuilder::StandardMazeBuilder() 
{
}
StandardMazeBuilder::~StandardMazeBuilder() 
{
}
void StandardMazeBuilder::buildRoom(int number, int column, int line) 
{
    Room * room = new Room(number);

    room->setSide(North, new Wall());
    room->setSide(East,  new Wall());
    room->setSide(South, new Wall());
    room->setSide(West,  new Wall());

    currentMaze->addRoom(room,column,line);
}
void StandardMazeBuilder::buildDoor(int roomFrom, int roomTo) 
{
    Room *rFrom = currentMaze->roomNo(roomFrom);
    Room *rTo   = currentMaze->roomNo(roomTo);

    Door* door = new Door(rFrom,rTo);

    MapSite * tmp = NULL;

    tmp = rFrom->getSide(East);
    if (tmp){
        rFrom->setSide(East,NULL);
        delete(tmp);
    }

    tmp = rTo->getSide(West);
    if (tmp){
        rTo->setSide(West,NULL);
        delete(tmp);
    }

    rFrom->setSide(East, door);
    rTo->setSide(West, door);
}

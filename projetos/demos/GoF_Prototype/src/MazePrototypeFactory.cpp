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
#include "MazePrototypeFactory.h"

MazePrototypeFactory::MazePrototypeFactory(Maze * maze, Wall * wall, Room * room, Door * door)
{
    mazeType = maze;
    wallType = wall;
    roomType = room;
    doorType = door;
}
MazePrototypeFactory::~MazePrototypeFactory()
{
    if (mazeType){
        delete(mazeType);
    }
    if (wallType){
        delete(wallType);
    }
    if (roomType){
        delete(roomType);
    }
    if (doorType){
        delete(doorType);
    }
}
Room * MazePrototypeFactory::makeRoom(int number)
{
    Room * room = roomType->clone();
    room->initialize(number);

    return room;
}
Door * MazePrototypeFactory::makeDoor(Room * room1, Room * room2)
{
    Door * door = doorType->clone();
    door->initialize(room1,room2);
    return door;
}
Maze * MazePrototypeFactory::makeMaze()
{
    return mazeType->clone();
}
Wall * MazePrototypeFactory::makeWall()
{
    return wallType->clone();
}

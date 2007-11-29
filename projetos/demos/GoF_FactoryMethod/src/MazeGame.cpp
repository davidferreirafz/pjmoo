//***************************************************************************
//  UML <Demo - GoF - Designer Patterns>
//  Copyright (C) 2007 by David Ferreira - FZ
//  davidferreira.fz@gmail.com - http://pjmoo.wiki.sourceforge.net/GoF
//***************************************************************************
//    Este programa � software livre; voc� pode redistribu�-lo e/ou
//    modific�-lo sob os termos da Licen�a P�blica Geral GNU, conforme
//    publicada pela Free Software Foundation; tanto a vers�o 2 da 
//    Licen�a como (a seu crit�rio) qualquer vers�o mais nova.
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
#include "MazeGame.h"

MazeGame::MazeGame() 
{
}
MazeGame::~MazeGame() 
{
}
Maze * MazeGame::create() 
{
    Maze* aMaze = makeMaze();

    Room* r1 = makeRoom(1);
    Room* r2 = makeRoom(2);

    Door* theDoor = makeDoor(r1,r2);


    aMaze->addRoom(r1,8,6);
    aMaze->addRoom(r2,10,6);


    r1->setSide(North, makeWall());
    r1->setSide(East,  theDoor);
    r1->setSide(South, makeWall());
    r1->setSide(West,  makeWall());

    r2->setSide(North, makeWall());
    r2->setSide(East,  makeWall());
    r2->setSide(South, makeWall());
    r2->setSide(West,  theDoor);

    return aMaze;
}
Maze * MazeGame::makeMaze() 
{
    return new Maze();
}
Wall * MazeGame::makeWall() 
{
    return new Wall();
}
Room * MazeGame::makeRoom(int number) 
{
    return new Room(number);
}
Door * MazeGame::makeDoor(Room * room1, Room * room2) 
{
    return new Door(room1,room2);
}

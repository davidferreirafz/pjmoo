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
#include "MazeGame.h"

MazeGame::MazeGame() 
{
}
MazeGame::~MazeGame() 
{
}
Maze * MazeGame::create() 
{
    Maze * aMaze = new Maze();

    Room* r1 = new Room(1);
    Room* r2 = new Room(2);

    Door* theDoor = new Door(r1,r2);

    aMaze->addRoom(r1,8,6);
    aMaze->addRoom(r2,10,6);


    r1->setSide(North, new Wall);
    r1->setSide(East, theDoor);
    r1->setSide(South, new Wall);
    r1->setSide(West, new Wall);

    r2->setSide(North, new Wall);
    r2->setSide(East, new Wall);
    r2->setSide(South, new Wall);
    r2->setSide(West, theDoor);

    return aMaze;
}

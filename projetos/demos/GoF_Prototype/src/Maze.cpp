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
#include "Maze.h"

Maze::Maze() 
{
    for (int x=0; x<19; x++){
        for (int y=0; y<14; y++){
            rooms[x][y]=NULL;
        }
    }
}
Maze::Maze(const Maze & source) 
{
    for (int x=0; x<19; x++){
        for (int y=0; y<14; y++){
            rooms[x][y]=source.rooms[x][y];
        }
    }
}
Maze::~Maze() 
{
    for (int x=0; x<19; x++){
        for (int y=0; y<14; y++){
            if (rooms[x][y]!=NULL){
                delete(rooms[x][y]);
            }
        }
    }
}
void Maze::addRoom(Room * room, int column, int line) 
{
    rooms[column][line]=room;
}
Room * Maze::roomNo(int number) const 
{
    Room * room = NULL;
    for (int x=0; x<19; x++){
        for (int y=0; y<14; y++){
            if (rooms[x][y]->getNumber()==number){
                room = rooms[x][y];
            }
        }
    }

    return room;
}
void Maze::draw() 
{
    int xVirtual=0;
    int yVirtual=0;

    for (int x=0; x<19; x++){
        for (int y=0; y<14; y++){
            if (rooms[x][y]!=NULL){

                xVirtual=(x*32)+32;
                yVirtual=(y*32)+32;
                rooms[x][y]->draw(xVirtual,yVirtual);
            }
        }
    }
}
Maze * Maze::clone() 
{
    return new Maze(*this);
}

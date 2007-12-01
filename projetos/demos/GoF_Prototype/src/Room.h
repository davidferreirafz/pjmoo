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
#ifndef _ROOM_H
#define _ROOM_H

#include "MapSite.h"

class Room : public MapSite
{
  public:
    Room(int number);

    Room(const Room & source);

    virtual ~Room();

    virtual void enter();

    virtual void draw(int x, int y);

    void setSide(Direction direction, MapSite * map);

    MapSite * getSide(Direction direction) const;

    Direction getDirection(MapSite * map);

    int getNumber();


  protected:
    int roomNumber;

    MapSite * sides[4];


  public:
    virtual Room * clone() const;

    void initialize(int number);

    virtual void load();

};
#endif

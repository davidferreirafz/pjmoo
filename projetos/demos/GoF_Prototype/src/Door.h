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
#ifndef _DOOR_H
#define _DOOR_H

#include "MapSite.h"
#include "Room.h"

class Door : public MapSite
{
  public:
    Door(Room * room1, Room * room2);

    Door(const Door & source);

    virtual ~Door();

    virtual void enter();

    virtual Door * clone() const;

    void initialize(Room * room1, Room * room2);

    Room * otherSideFrom(Room * theRoom);


  protected:
    virtual void load();


  private:
    Room * room[2];

    bool open;

};
#endif
